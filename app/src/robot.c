#include "robot.h"

#include "robot_tasks.h"
#include "chassis_task.h"
#include "gimbal_task.h"
#include "launch_task.h"
#include "remote.h"
#include "bsp_can.h"
#include "gimbal_task.h"
#include <math.h>
#include "imu_task.h"
#include "user_math.h"
#include "referee_system.h"
#include "buzzer.h"
#include "user_math.h"
#include "supercap.h"

extern DJI_Motor_Handle_t *g_yaw;

#define KEYBOARD_RAMP_COEF (0.004f)
#define SPINTOP_COEF (0.003f)
#define MAX_SPEED (1.0f)

Robot_State_t g_robot_state = {0};
extern Remote_t g_remote;
extern Supercap_t g_supercap;

void _toggle_robot_state(uint8_t *state);

/**
 * @brief This function initializes the robot.
 * This means setting the state to STARTING_UP,
 * initializing the buzzer, and calling the
 * Robot_Task_Start() for the task scheduling
 */
void Robot_Init()
{
    g_robot_state.state = STARTING_UP;

    Buzzer_Init();
    Melody_t system_init_melody = {
        .notes = SYSTEM_INITIALIZING,
        .loudness = 0.5f,
        .note_num = SYSTEM_INITIALIZING_NOTE_NUM,
    };
    Buzzer_Play_Melody(system_init_melody); // TODO: Change to non-blocking

    //   Initialize all tasks
    Robot_Tasks_Start();
}

void Handle_Starting_Up_State()
{
    // Initialize all hardware
    Chassis_Task_Init();
    Gimbal_Task_Init();
    Launch_Task_Init();
    Remote_Init(&huart3);
    CAN_Service_Init();
    Referee_System_Init(&huart1);
    Supercap_Init(&g_supercap);

    // Set robot state to disabled
    g_robot_state.state = DISABLED;
}

void Handle_Enabled_State()
{
    if (g_remote.online_flag == REMOTE_OFFLINE || g_remote.controller.right_switch == DOWN)
    {
        g_robot_state.state = DISABLED;
        g_robot_state.launch.IS_FLYWHEEL_ENABLED = 0;
    }
    else
    {
        // Process movement and components in enabled state
        Referee_Set_Robot_State();
        Process_Remote_Input();
        Process_Chassis_Control();
        Process_Gimbal_Control();
        Process_Launch_Control();
    }
}

void Handle_Disabled_State()
{
    // Disable all major components
    g_robot_state.launch.IS_FLYWHEEL_ENABLED = 0;
    g_robot_state.chassis.x_speed = 0;
    g_robot_state.chassis.y_speed = 0;
    g_robot_state.gimbal.gimbal_yaw_angle = 0;
    g_robot_state.gimbal.gimbal_pitch_angle = 0;
}

void Process_Remote_Input()
{
}

void Process_Chassis_Control()
{
}

void Process_Gimbal_Control()
{
    Gimbal_Ctrl_Loop();
}

void Process_Launch_Control()
{
}

/**
 *  This function is called periodically by the Robot Task.
 *  It serves as the top level state machine for the robot based on the current state.
 *  Appropriate functions are called.
 */
void Robot_Command_Loop()
{
    switch (g_robot_state.state)
    {
    case STARTING_UP:
        Handle_Starting_Up_State();
        break;
    case DISABLED:
        Handle_Disabled_State();
        break;
    case ENABLED:
        Handle_Enabled_State();
        break;
    default:
        Error_Handler();
        break;
    }
}

void _toggle_robot_state(uint8_t *state)
{
    *state ^= 0x01;
}