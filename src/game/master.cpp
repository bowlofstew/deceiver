#include "master.h"
#include "asset/level.h"

namespace VI
{

namespace Net
{

namespace Master
{

#define DEBUG_MSG 0
#define NET_MASTER_RESEND_INTERVAL 0.5

Save::Save()
{
	reset();
}

void Save::reset()
{
	this->~Save();

	memset(this, 0, sizeof(*this));

	zone_last = AssetNull;
	zone_current = AssetNull;
	zone_overworld = AssetNull;
	locke_index = -1;

	zones[Asset::Level::Docks] = ZoneState::ParkourUnlocked;

	resources[s32(Resource::Energy)] = s16(ENERGY_INITIAL * 3.5f);
}

Messenger::Peer::Peer()
	: incoming_seq(NET_SEQUENCE_COUNT - 1),
	outgoing_seq(0)
{

}

SequenceID Messenger::outgoing_sequence_id(const Sock::Address& addr) const
{
	auto i = sequence_ids.find(addr.hash());
	if (i == sequence_ids.end())
		return 0;
	else
		return i->second.outgoing_seq;
}

b8 Messenger::has_unacked_outgoing_messages(const Sock::Address& addr) const
{
	for (s32 i = 0; i < outgoing.length; i++)
	{
		if (outgoing[i].addr.equals(addr))
			return true;
	}
	return false;
}

b8 Messenger::add_header(StreamWrite* p, const Sock::Address& addr, Message type)
{
	using Stream = StreamWrite;
	SequenceID seq = outgoing_sequence_id(addr);
	{
		s16 version = GAME_VERSION;
		serialize_s16(p, version);
	}
	serialize_int(p, SequenceID, seq, 0, NET_SEQUENCE_COUNT - 1);
#if DEBUG_MSG
	vi_debug("Sending seq %d message %d to %s:%hd", s32(seq), s32(type), Sock::host_to_str(addr.host), addr.port);
#endif
	serialize_enum(p, Message, type);
	return true;
}

void Messenger::send(const StreamWrite& p, r64 timestamp, const Sock::Address& addr, Sock::Handle* sock)
{
	last_sent_timestamp = timestamp;
	SequenceID seq = outgoing_sequence_id(addr);

	OutgoingPacket* packet = outgoing.add();
	packet->data = p;
	packet->sequence_id = seq;
	packet->timestamp = timestamp;
	packet->addr = addr;

	SequenceID seq_next = sequence_advance(seq, 1);
	{
		u64 hash = addr.hash();
		auto i = sequence_ids.find(hash);
		if (i == sequence_ids.end())
		{
			// haven't sent a message to this address yet
			Peer peer;
			peer.outgoing_seq = seq_next;
			sequence_ids[hash] = peer;
		}
		else // update existing sequence ID
			i->second.outgoing_seq = seq_next;
	}

	Sock::udp_send(sock, addr, p.data.data, p.bytes_written());
}

b8 messenger_send_ack(SequenceID seq, Sock::Address addr, Sock::Handle* sock)
{
	using Stream = StreamWrite;
	StreamWrite p;
	packet_init(&p);
	{
		s16 version = GAME_VERSION;
		serialize_s16(&p, version);
	}
	serialize_int(&p, SequenceID, seq, 0, NET_SEQUENCE_COUNT - 1);
	{
		Message ack_type = Message::Ack;
		serialize_enum(&p, Message, ack_type);
	}
	packet_finalize(&p);
	Sock::udp_send(sock, addr, p.data.data, p.bytes_written());
	return true;
}

// returns true if the packet is in order and should be processed
void Messenger::received(Message type, SequenceID seq, const Sock::Address& addr, Sock::Handle* sock)
{
	if (type == Message::Ack)
	{
		// they are acking a sequence we sent
		// remove that sequence from our outgoing queue

		for (s32 i = 0; i < outgoing.length; i++)
		{
			if (outgoing[i].sequence_id == seq)
			{
				outgoing.remove(i);
				break;
			}
		}
	}
	else if (type != Message::Disconnect)
	{
		// when we receive any kind of message other than an ack, we must send an ack back

#if DEBUG_MSG
		vi_debug("Received seq %d message %d from %s:%hd", s32(seq), s32(type), Sock::host_to_str(addr.host), addr.port);
#endif

		messenger_send_ack(seq, addr, sock);
	}
}

void Messenger::update(r64 timestamp, Sock::Handle* sock, s32 max_outgoing)
{
	if (max_outgoing > 0 && outgoing.length > max_outgoing)
		reset();
	else
	{
		r64 timestamp_cutoff = timestamp - NET_MASTER_RESEND_INTERVAL;
		for (s32 i = 0; i < outgoing.length; i++)
		{
			OutgoingPacket* packet = &outgoing[i];
			if (packet->timestamp < timestamp_cutoff)
			{
#if DEBUG_MSG
				vi_debug("Resending seq %d to %s:%hd", s32(packet->sequence_id), Sock::host_to_str(packet->addr.host), packet->addr.port);
#endif
				packet->timestamp = timestamp;
				Sock::udp_send(sock, packet->addr, packet->data.data.data, packet->data.bytes_written());
			}
		}
	}
}

void Messenger::reset()
{
#if DEBUG_MSG
	vi_debug("%s", "Resetting all connections");
#endif
	outgoing.length = 0;
	sequence_ids.clear();
}

void Messenger::remove(const Sock::Address& addr)
{
#if DEBUG_MSG
	vi_debug("Removing peer %s:%hd", Sock::host_to_str(addr.host), addr.port);
#endif
	for (s32 i = 0; i < outgoing.length; i++)
	{
		if (outgoing[i].addr.equals(addr))
		{
			outgoing.remove(i);
			i--;
		}
	}
	sequence_ids.erase(addr.hash());
}

}

}

}
