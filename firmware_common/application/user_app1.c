/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{  

  LCDCommand(LCD_CLEAR_CMD); 
  
   LCDMessage(LINE1_START_ADDR,  "        HI!      ");  
   
   LCDMessage(LINE2_START_ADDR,"      LET'S GO!  ");  
   
   
   PWMAudioSetFrequency(BUZZER1, 500);

  LedBlink(RED, LED_1HZ);
  LedBlink(ORANGE, LED_0_5HZ);
  LedBlink(YELLOW, LED_1HZ);
  LedBlink(GREEN, LED_0_5HZ);
  LedBlink(CYAN, LED_1HZ);
  LedBlink(BLUE, LED_0_5HZ);
  LedBlink(PURPLE, LED_1HZ);
   
/* Start with red LED on 100%, green and blue off */
  LedPWM(LCD_RED, LED_PWM_100);
  LedPWM(LCD_GREEN, LED_PWM_100);
  LedPWM(LCD_BLUE, LED_PWM_100);
   
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{  //按键0
   if( WasButtonPressed(BUTTON0) )
  {  
    
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR,  "       MUSIC      ");  
    LedPWM(LCD_RED, LED_PWM_100);
    LedPWM(LCD_GREEN, LED_PWM_0);
    LedPWM(LCD_BLUE, LED_PWM_0);
    
  static u16 u16BlinkCount = 0;

u16BlinkCount++;
if(u16BlinkCount == 100)
{
  LedOn(GREEN);
  LedOn(CYAN);
  u16BlinkCount++;
}
if(u16BlinkCount == 400)
{
 LedOn(BLUE);
 LedOn(YELLOW);
  u16BlinkCount++;
}
if(u16BlinkCount == 700)
{
  LedOn(PURPLE); 
  LedOn(ORANGE);
  u16BlinkCount++;
}
if(u16BlinkCount == 1000)
{
  LedOn(RED);
  LedOn(WHITE); 
  u16BlinkCount++;
}

if(u16BlinkCount == 1300)
{
  LedOff(RED);
  LedOff(WHITE); 
  u16BlinkCount++;
}
if(u16BlinkCount == 1600)
{
  LedOff(PURPLE); 
  LedOff(ORANGE);
  u16BlinkCount++;
}
if(u16BlinkCount == 1900)
{
 LedOff(BLUE);
 LedOff(YELLOW);
  u16BlinkCount++;
}
if(u16BlinkCount == 2200)
{
  LedOff(GREEN);
  LedOff(CYAN);
  u16BlinkCount=0;}
    
    
    
    static u16 au16NotesRight[]    = {NO, B4, C5, E5, D5 ,C5, B4, G4, A4, B4, A4, G4, E4, G4, A4, G4, A4, G4, A5, G4, F4, G3, NO, A4, C5, A4, D5, NO, E4, G4, E4, A4, NO, G4, A4, E5, D5, C5, B4, E4, NO, NO};
  static u16 au16DurationRight[] = {QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, HN, QN, QN, EN, HN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, HN, QN, QN, QN, EN, HN, QN, QN, QN, QN, HN, QN, QN, FN, FN,};
  static u16 au16NoteTypeRight[] = {HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, RT, RT};
  static u8 u8IndexRight = 0;
  static u32 u32RightTimer = 0;
  static u16 u16CurrentDurationRight = 0;
  static u16 u16NoteSilentDurationRight = 0;
  static bool bNoteActiveNextRight = TRUE;

  u8 u8CurrentIndex;
  
    if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight))
  {
    u32RightTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexRight;
    
    /* Set up to play current note */
    if(bNoteActiveNextRight)
    {
           if(au16NoteTypeRight[u8CurrentIndex] == RT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationRight = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextRight = FALSE;
      } /* end RT case */
    
      else if(au16NoteTypeRight[u8CurrentIndex] == ST)
      {
        u16CurrentDurationRight = STACCATO_NOTE_TIME;
        u16NoteSilentDurationRight = au16DurationRight[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextRight = FALSE;
      } /* end ST case */

      else if(au16NoteTypeRight[u8CurrentIndex] == HT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex];
        u16NoteSilentDurationRight = 0;
        bNoteActiveNextRight = TRUE;

        u8IndexRight++;
        if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
        {
          u8IndexRight = 0;
        }
      } /* end HT case */


      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesRight[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER1, au16NotesRight[u8CurrentIndex]);
        PWMAudioOn(BUZZER1);
      }
      else
      {                
        PWMAudioOff(BUZZER1);
      }
    } /* end if(bNoteActiveNextRight) */

    else
    {
      /* No active note */
      PWMAudioOff(BUZZER1);
      u32RightTimer = G_u32SystemTime1ms;
      u16CurrentDurationRight = u16NoteSilentDurationRight;
      bNoteActiveNextRight = TRUE;
 
      u8IndexRight++;
      if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
      {
        u8IndexRight = 0;
      }
    } /* end else if(bNoteActiveNextRight) */
  } /* end if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight)) */

  
  }
  
 
 
 
 //按键1
  if( WasButtonPressed(BUTTON1) )
  {     
     ButtonAcknowledge(BUTTON0);

    LedPWM(LCD_RED, LED_PWM_0);
    LedPWM(LCD_GREEN, LED_PWM_0);
    LedPWM(LCD_BLUE, LED_PWM_100);
     
  
     static u16 u16BlinkCount = 0;

   u16BlinkCount++;
if(u16BlinkCount == 100)
{
  LedOn(WHITE);
  u16BlinkCount++;
}
if(u16BlinkCount == 200)
{
 LedOn(PURPLE);
  u16BlinkCount++;
}
if(u16BlinkCount == 300)
{
  LedOn(BLUE);
  u16BlinkCount++;
}
if(u16BlinkCount == 400)
{
  LedOn(CYAN);
  u16BlinkCount++;
}



if(u16BlinkCount == 500)
{
  LedOn(GREEN);
  u16BlinkCount++;
}
if(u16BlinkCount == 600)
{
 LedOn(YELLOW);
  u16BlinkCount++;
}
if(u16BlinkCount == 700)
{
  LedOn(ORANGE);
  u16BlinkCount++;
}
if(u16BlinkCount == 800)
{
  LedOn(RED);
  u16BlinkCount++;
}

if(u16BlinkCount == 900)
{
  
  LedOff(WHITE); 
  u16BlinkCount++;
}
if(u16BlinkCount == 1000)
{
 
  LedOff(PURPLE);
  u16BlinkCount++;
}
if(u16BlinkCount == 1100)
{
 
 LedOff(BLUE);
  u16BlinkCount++;
}
if(u16BlinkCount == 1200)
{

  LedOff(CYAN);
  u16BlinkCount++;
}


if(u16BlinkCount == 1300)
{
  LedOff(GREEN);
  
  u16BlinkCount++;
}
if(u16BlinkCount == 1400)
{
  LedOff(YELLOW); 
 
  u16BlinkCount++;
}
if(u16BlinkCount == 1500)
{
 LedOff(ORANGE);
 
  u16BlinkCount++;
}


if(u16BlinkCount == 1600)
{
  LedOff(RED);
  
  u16BlinkCount=0;
}


    
    
    
    
  static u16 au16NotesRight[]    = {NO,C4,C3,C4,C3,C4,E4,G3,E4,E4,D4,C4,B3,C4,A3,C4,C4,B3,C4,D4,NO,B3,G3,G3,G3,NO,G3,G3,A3,C4,C4,C4,C4,B3,C4,D4,C4,A3,C4,A3,E4,C4,C4,E4,D4,D4,C4,E4,D4,D4,C4,C4,D4,NO,C4,B3,C4,B3,C4,E4,G3,E4,E4,D4,C4,B3,C4,A3,C4,C4,C4,B3,C4,D4,G3,E4,E4,E4,NO,A3,B3};
  static u16 au16DurationRight[] = {FN, QN, QN, QN, QN, QN, QN, FN, EN, EN, QN, QN, QN, QN, QN, QN, FN, QN, EN, EN, QN, QN, QN, QN,FN,QN,EN,EN,FN,QN,FN,EN,EN,QN,QN,QN,FN,EN,EN,QN,QN,QN,FN,QN,QN,QN,QN,QN,QN,QN,QN,QN,FN,QN,QN,QN,QN,QN,QN,QN,FN,EN,EN,QN,QN,QN,QN,QN,QN,FN,EN,QN,EN,QN,QN,QN,QN,FN,QN,EN,EN};
  static u16 au16NoteTypeRight[] = {HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT};
  static u8 u8IndexRight = 0;
  static u32 u32RightTimer = 0;
  static u16 u16CurrentDurationRight = 0;
  static u16 u16NoteSilentDurationRight = 0;
  static bool bNoteActiveNextRight = TRUE;

  u8 u8CurrentIndex;
  
    if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight))
  {
    u32RightTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexRight;
    
    /* Set up to play current note */
    if(bNoteActiveNextRight)
    {
           if(au16NoteTypeRight[u8CurrentIndex] == RT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationRight = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextRight = FALSE;
      } /* end RT case */
    
      else if(au16NoteTypeRight[u8CurrentIndex] == ST)
      {
        u16CurrentDurationRight = STACCATO_NOTE_TIME;
        u16NoteSilentDurationRight = au16DurationRight[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextRight = FALSE;
      } /* end ST case */

      else if(au16NoteTypeRight[u8CurrentIndex] == HT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex];
        u16NoteSilentDurationRight = 0;
        bNoteActiveNextRight = TRUE;

        u8IndexRight++;
        if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
        {
          u8IndexRight = 0;
        }
      } /* end HT case */


      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesRight[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER1, au16NotesRight[u8CurrentIndex]);
        PWMAudioOn(BUZZER1);
      }
      else
      {                
        PWMAudioOff(BUZZER1);
      }
    } /* end if(bNoteActiveNextRight) */

    else
    {
      /* No active note */
      PWMAudioOff(BUZZER1);
      u32RightTimer = G_u32SystemTime1ms;
      u16CurrentDurationRight = u16NoteSilentDurationRight;
      bNoteActiveNextRight = TRUE;
 
      u8IndexRight++;
      if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
      {
        u8IndexRight = 0;
      }
    } /* end else if(bNoteActiveNextRight) */
  } /* end if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight)) */


  }
  
  
  //按键2
  
  if( WasButtonPressed(BUTTON2) )
  {     

    ButtonAcknowledge(BUTTON1);


        LedPWM(LCD_RED, LED_PWM_20);
    LedPWM(LCD_GREEN, LED_PWM_100);
    LedPWM(LCD_BLUE, LED_PWM_0);
    
  static u16 u16BlinkCount = 0;

u16BlinkCount++;
if(u16BlinkCount == 100)
{
  LedOn(WHITE);
  LedOn(RED);
  u16BlinkCount++;
}
if(u16BlinkCount == 400)
{
 LedOn(PURPLE);
 LedOn(ORANGE);
  u16BlinkCount++;
}
if(u16BlinkCount == 700)
{
  LedOn(BLUE); 
  LedOn(YELLOW);
  u16BlinkCount++;
}
if(u16BlinkCount == 1000)
{
  LedOn(CYAN);
  LedOn(GREEN); 
  u16BlinkCount++;
}

if(u16BlinkCount == 1300)
{
  LedOff(CYAN);
  LedOff(GREEN); 
  u16BlinkCount++;
}
if(u16BlinkCount == 1600)
{
  LedOff(BLUE); 
  LedOff(YELLOW);
  u16BlinkCount++;
}
if(u16BlinkCount == 1900)
{
 LedOff(PURPLE);
 LedOff(ORANGE);
  u16BlinkCount++;
}
if(u16BlinkCount == 2200)
{
  LedOff(WHITE);
  LedOff(RED);
  u16BlinkCount=0;}

  
  static u16 au16NotesRight[]    = {G4,A4,B4,E4,NO,      B4,A4,G4,A4,D4,NO,    D5,C5,D5,B4,NO,     G4,E4,G4,A4,G4,B4,NO,NO,
G4,A4,B4,   B4,E5,    E5,A4,  B4,A4,    A4,D5,NO,        B4,G4,G4,NO,     G4,E4,G4,A4,G4,G4};
  static u16 au16DurationRight[] = {EN,QN,QN,QN,SN,   EN,EN,QN,QN,HN,QN,     EN,EN,QN,QN,SN,    EN,EN,EN,EN,QN,HN,QN,QN,
EN,QN,QN,  EN,QN,    EN,QN,  EN,QN,   QN,QN,QN, EN,EN,QN,EN,   EN,QN,EN,QN,QN,HN};
  static u16 au16NoteTypeRight[] = {RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,
RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT};
  
    static u8 u8IndexRight = 0;
  static u32 u32RightTimer = 0;
  static u16 u16CurrentDurationRight = 0;
  static u16 u16NoteSilentDurationRight = 0;
  static bool bNoteActiveNextRight = TRUE;
    u8 u8CurrentIndex;
    if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight))
  {
    u32RightTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexRight;
    
    /* Set up to play current note */
    if(bNoteActiveNextRight)
    {
           if(au16NoteTypeRight[u8CurrentIndex] == RT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationRight = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextRight = FALSE;
      } /* end RT case */
    
      else if(au16NoteTypeRight[u8CurrentIndex] == ST)
      {
        u16CurrentDurationRight = STACCATO_NOTE_TIME;
        u16NoteSilentDurationRight = au16DurationRight[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextRight = FALSE;
      } /* end ST case */

      else if(au16NoteTypeRight[u8CurrentIndex] == HT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex];
        u16NoteSilentDurationRight = 0;
        bNoteActiveNextRight = TRUE;

        u8IndexRight++;
        if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
        {
          u8IndexRight = 0;
        }
      } /* end HT case */

      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesRight[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER1, au16NotesRight[u8CurrentIndex]);
        PWMAudioOn(BUZZER1);
      }
      else
      {                
        PWMAudioOff(BUZZER1);
      }
    } /* end if(bNoteActiveNextRight) */
    else
    {
      /* No active note */
      PWMAudioOff(BUZZER1);
      u32RightTimer = G_u32SystemTime1ms;
      u16CurrentDurationRight = u16NoteSilentDurationRight;
      bNoteActiveNextRight = TRUE;
 
      u8IndexRight++;
      if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
      {
        u8IndexRight = 0;
      }
    } /* end else if(bNoteActiveNextRight) */
 
  } /* end if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight)) */
}
 

//按键3
 if( WasButtonPressed(BUTTON3) )
  {  
    ButtonAcknowledge(BUTTON2);
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR,  "       MUSIC      ");  
    LedPWM(LCD_RED, LED_PWM_100);
    LedPWM(LCD_GREEN, LED_PWM_0);
    LedPWM(LCD_BLUE, LED_PWM_100);
    
    static u16 u16BlinkCount = 0;

u16BlinkCount++;
if(u16BlinkCount == 100)
{
  LedBlink(WHITE,LED_2HZ);
  LedBlink(RED,LED_2HZ);
   LedBlink(BLUE,LED_2HZ);
    LedOn(GREEN);
     LedOn(ORANGE);
      LedBlink(YELLOW,LED_2HZ);
        LedOn(CYAN);
         LedOn(PURPLE);
  u16BlinkCount++;
 
}

static u16 au16NotesRight[]    = { E4, G4, A4, A4, C5, D5, E5, G5, E5, D5, C5, A4, E5, D5, A4, C4, E5, D5, A4, C4, C4, C4, D4, E4, B4, E4, G4, A4, C4, A4, C5, D5, B4, E5, G5 ,E5, E4, D5, C5, A4, C4, E5, D5, A4, C4, E5, D5, A4, G4, A4, C4, E4, B4, C5};
  static u16 au16DurationRight[] = {QN, QN, HN, QN, QN, HN, QN, QN, HN, QN, QN, HN, QN, QN, QN, QN, QN, QN, HN, HN, QN, QN, QN, QN, HN, HN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, QN, FN, FN, QN, QN, QN, QN, FN};
  static u16 au16NoteTypeRight[] = { HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT, HT,};
    static u8 u8IndexRight = 0;
  static u32 u32RightTimer = 0;
  static u16 u16CurrentDurationRight = 0;
  static u16 u16NoteSilentDurationRight = 0;
  static bool bNoteActiveNextRight = TRUE;

  u8 u8CurrentIndex;
  
    if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight))
  {
    u32RightTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexRight;
    
    /* Set up to play current note */
    if(bNoteActiveNextRight)
    {
           if(au16NoteTypeRight[u8CurrentIndex] == RT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationRight = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextRight = FALSE;
      } /* end RT case */
    
      else if(au16NoteTypeRight[u8CurrentIndex] == ST)
      {
        u16CurrentDurationRight = STACCATO_NOTE_TIME;
        u16NoteSilentDurationRight = au16DurationRight[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextRight = FALSE;
      } /* end ST case */

      else if(au16NoteTypeRight[u8CurrentIndex] == HT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex];
        u16NoteSilentDurationRight = 0;
        bNoteActiveNextRight = TRUE;

        u8IndexRight++;
        if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
        {
          u8IndexRight = 0;
        }
      } /* end HT case */


      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesRight[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER1, au16NotesRight[u8CurrentIndex]);
        PWMAudioOn(BUZZER1);
      }
      else
      {                
        PWMAudioOff(BUZZER1);
      }
    } /* end if(bNoteActiveNextRight) */

    else
    {
      /* No active note */
      PWMAudioOff(BUZZER1);
      u32RightTimer = G_u32SystemTime1ms;
      u16CurrentDurationRight = u16NoteSilentDurationRight;
      bNoteActiveNextRight = TRUE;
 
      u8IndexRight++;
      if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
      {
        u8IndexRight = 0;
      }
    } /* end else if(bNoteActiveNextRight) */
  } /* end if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight)) */


  
  
  }}
/* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{

  

}
  
/* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
