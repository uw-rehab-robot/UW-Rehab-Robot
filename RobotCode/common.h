bool onLine();//returns whether or not the robot can detect a line
float getRatio();//gets the turn ratio from the raw sensor data
void storeData();
void readSensor();
float percentDiff();
int getMax();
int getMin();
void blink();
void setMaxSpeed();

//#define SECOND 1000; //1000 milliseconds per second
//#define MINUTE 60000; //60,000 milliseconds per minute
int SECOND = 1000;
int MINUTE = 60000;
//unsigned long deltaTime; //change in time variable. used to determine elapsed time
//unsigned long prevTime;
unsigned long RUN_TIME = 1 * MINUTE; //decides how long to run our code, 60,000 is one minute, the second number multiplies that minute

/////////// pin definitions
const int IRSensor[] = {A2, A1, A0, A7, A6}; //Pins reflect current wiring (2/18/2020)

const int NUM_SENSORS = 5;

// to be set when the sensor max and min are known, and put here to improve code flexibility if we change sensors at any point.
const int SENSOR_MAX = 1024;
const int SENSOR_MIN = 0;

//Initialize max and min IR here, they will be the 'modified' values
int maxIR = SENSOR_MAX;
int minIR = SENSOR_MIN;

//Initialize IRdirection. This will be a value from 0-1 that determines our direction, with 0 is left, 1 is right, and 0.5 is forward
float IRdirection;

//Initialize array to store sensor values
int sensorDataRaw[NUM_SENSORS];

const int CALIBRATION_TIME = 15 * SECOND; // sets the calibration time to 15 seconds., not using rn

const float TURN_THRESHOLD = 0.1; // defines the threshold the deviation must reach before turning.
//float tempPercentDiff;            //placeholder for the percent difference

//These are the multipliers were using to assign weight to inner and outer sensors
const int INNER_WEIGHT = 2;
const int OUTER_WEIGHT = 3;
const float CENTER_WEIGHT = 1; //Dont know if we'll need the center weight, I think I found a workaround

// stores the scale factors used in weighted turning.
const float weightArray[] = {-OUTER_WEIGHT, -INNER_WEIGHT, CENTER_WEIGHT, INNER_WEIGHT, OUTER_WEIGHT};

//Initialize variables for data collection
int logIndex = 0;
const int dataPoints = 50;
int sensorLog[dataPoints][NUM_SENSORS];

//                   initialize motor variables

const int DRIVE_TIME = 10; //Defines how long (in milliseconds) motors drive in forward functions. Keep this very low to reduce wagging
const byte SPEED = 100;

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = -1; //                                                     Change one of these, can't remember which

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins,
// CHANGE THESE UPON WIRING

//Digital
#define AIN1 7
#define BIN1 5
#define AIN2 8
#define BIN2 4
#define PWMA 9
#define PWMB 3
//Optional
#define STBY 6

//Not using
//const byte DRIVE_TIME = 1; //in milliseconds
class Timer
{
private:
    void updateTime()
    {
        prevTime = millis();
    }
    long interval;
    bool timeElapsedFlag;

public:
    unsigned long deltaTime;
    unsigned long prevTime;

    Timer(long intervalIn)
    {
        interval = intervalIn;
        prevTime = millis();
        deltaTime = 0;
        timeElapsedFlag = false;
    }
    bool timeElapsed()
    {
        deltaTime = millis() - prevTime;
        if (deltaTime >= interval)
        {
            timeElapsedFlag = true;
            updateTime();
        }
        return timeElapsedFlag;
    }
};