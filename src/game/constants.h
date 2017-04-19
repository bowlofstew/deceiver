#pragma once

// NOTE: this is also the max number of teams
// if you change this, make sure to allocate more physics categories for each team's force field
#define MAX_PLAYERS 4

#define GAME_VERSION 1

#define MAX_USERNAME 255

#define MAX_BONES 72

#define UI_JOYSTICK_DEAD_ZONE 0.5f
#define SPAWN_DELAY 5.0f
#define ENERGY_INITIAL 0
#define ENERGY_MINION_KILL 5
#define ENERGY_SENSOR_DESTROY 5
#define ENERGY_FORCE_FIELD_DESTROY 5
#define ENERGY_ROCKET_DESTROY 5
#define ENERGY_GRENADE_DESTROY 5
#define ENERGY_DRONE_DESTROY 100
#define ENERGY_DEFAULT_INCREMENT 0
#define ENERGY_TURRET_DESTROY 100
#define ENERGY_CORE_MODULE_DESTROY 20
#define MAX_ABILITIES 3
#define DEFAULT_ASSAULT_DRONES 5
#define MATCH_TIME_DEFAULT (60.0f * 8.0f)

#define SPAWN_POINT_RADIUS 3.5f

#define UPGRADE_TIME 1.5f

#define ACTIVE_ARMOR_TIME 0.75f

#define ENERGY_INCREMENT_INTERVAL 15.0f

#define NET_TICK_RATE (1.0f / 60.0f)
#define NET_SYNC_TOLERANCE_POS 0.2f
#define NET_SYNC_TOLERANCE_ROT 0.2f
#define NET_INTERPOLATION_DELAY ((NET_TICK_RATE * 4.0f) + 0.02f)
#define NET_MAX_PACKET_SIZE 2000
#define NET_SEQUENCE_COUNT 1023
#define NET_SEQUENCE_INVALID NET_SEQUENCE_COUNT
#define NET_ACK_PREVIOUS_SEQUENCES 64
#define NET_MAX_SEQUENCE_GAP 180
#define NET_PREVIOUS_SEQUENCES_SEARCH NET_MAX_SEQUENCE_GAP
#define NET_TIMEOUT (256.0f * NET_TICK_RATE)
#define NET_MAX_MESSAGES_SIZE (NET_MAX_PACKET_SIZE / 2)
#define NET_SEQUENCE_RESEND_BUFFER NET_ACK_PREVIOUS_SEQUENCES
#define NET_HISTORY_SIZE 256
#define NET_MASTER_STATUS_INTERVAL 1.0f
#define NET_SERVER_IDLE_TIME 8.0f

#define MAX_ZONES 64

#define MAX_ENTITIES 2048

#define DRONE_DASH_SPEED 20.0f
#define DRONE_DASH_TIME 0.35f
#define DRONE_DASH_DISTANCE (DRONE_DASH_SPEED * DRONE_DASH_TIME)
#define DRONE_MAX_DISTANCE 25.0f
#define DRONE_RADIUS 0.2f
#define DRONE_VERTICAL_DOT_LIMIT 0.9998f
#define DRONE_VERTICAL_ANGLE_LIMIT ((PI * 0.5f) - 0.021f)

#define DRONE_HEALTH 1
#define DRONE_SHIELD 2
#define PARKOUR_SHIELD 2
#define SHIELD_REGEN_DELAY 9.0f
#define SHIELD_REGEN_TIME 2.0f
#define DRONE_FLY_SPEED 35.0f
#define DRONE_CRAWL_SPEED 2.25f
#define DRONE_COOLDOWN 2.0f
#define DRONE_LEGS 3
#define DRONE_INVINCIBLE_TIME 1.5f
#define DRONE_SNIPE_DISTANCE 100.0f
#define DRONE_CHARGES 3
#define DRONE_THIRD_PERSON_OFFSET 2.0f
#define DRONE_SHIELD_RADIUS 0.6f
#define DRONE_SHIELD_ALPHA 0.3f
#define DRONE_OVERSHIELD_ALPHA 0.5f
#define DRONE_OVERSHIELD_RADIUS (DRONE_SHIELD_RADIUS * 1.667f)
#define DRONE_SHIELD_VIEW_RATIO 0.6f

#define TURRET_HEIGHT 3.5f
#define TURRET_HEALTH 50
#define TURRET_VIEW_RANGE DRONE_MAX_DISTANCE

#define MAX_BONE_WEIGHTS 4

#define ROPE_SEGMENT_LENGTH 1.0f
#define ROPE_RADIUS 0.075f

#define SENSOR_LINGER_TIME 5.0f
#define SENSOR_TRACK_TIME 1.0f
#define SENSOR_RADIUS 0.2f
#define SENSOR_HEALTH 5
#define SENSOR_RANGE 14.0f

#define FORCE_FIELD_RADIUS 12.0f
#define FORCE_FIELD_BASE_OFFSET 0.95f
#define FORCE_FIELD_LIFETIME 8.0f

#define ROCKET_RANGE (DRONE_MAX_DISTANCE * 1.5f)
#define ROCKET_SPEED 12.0f

#define GRENADE_LAUNCH_SPEED 20.0f
#define GRENADE_RADIUS 0.125f
#define GRENADE_RANGE 14.0f
#define GRENADE_DELAY 1.5f

#define BOLT_SPEED 20.0f
#define BOLT_LENGTH 0.5f
#define BOLT_LIGHT_RADIUS 10.0f

#define BATTERY_RADIUS 0.55f

#define AIR_CONTROL_ACCEL 5.0f

#define TRANSITION_TIME 1.0f // time to transition between levels / overworld

#define PVP_ACCESSIBLE Vec4(0.7f, 0.7f, 0.7f, 1.0f)
#define PVP_ACCESSIBLE_NO_OVERRIDE Vec4(0.7f, 0.7f, 0.7f, MATERIAL_NO_OVERRIDE)
#define PVP_INACCESSIBLE Vec4(0.0f, 0.0f, 0.0f, MATERIAL_NO_OVERRIDE)

#define SCORE_SUMMARY_DELAY 2.0f
#define SCORE_SUMMARY_ACCEPT_DELAY 3.0f

#define ZONE_UNDER_ATTACK_TIME 90.0f
#define ZONE_UNDER_ATTACK_THRESHOLD 20.0f
#define ZONE_LOST_COOLDOWN (3.0f * 60.0f)

#define MAX_PATH_LENGTH 1024
#define AI_MAX_PATH_LENGTH 64

#define AI_RECORD_WAIT_TIME 1.0f