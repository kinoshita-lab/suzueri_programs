#include <MIDI.h>
#include "MsTimer2.h"
#include "Solenoider.h"
#include "Motor.h"

constexpr auto Number_Of_Solenoid = 4;
constexpr auto Number_Of_Motor = 2;

constexpr int Solenoid_Pins[Number_Of_Solenoid] = {13, 3, 4, 5}; // ソレノイドのピン
constexpr int Motor_Pins[Number_Of_Motor] = {6, 7}; // モーターのピン

constexpr auto Solenoid_On_Time_in_MilliSeconds = 50; // ソレノイドが動く時間(msec)
constexpr auto Motor_On_Time_in_MilliSeconds = 10 * 1000; // モーターが動く時間(msec)

constexpr int Solenoid_Midi_Notes[Number_Of_Solenoid] = {33, 38, 96, 100}; // ソレノイドが受けつけるノート番号
constexpr int Motor_Midi_Notes[Number_Of_Solenoid] = {41, 91}; // モーターが受けつけるノート番号

Solenoider solenoiders[Number_Of_Solenoid];
Motor motors[Number_Of_Motor];

MIDI_CREATE_DEFAULT_INSTANCE();
auto tick1ms() -> void
{
 for (auto&& s : solenoiders) {
   s.tick();
 }

 for (auto&& m : motors) {
   m.tick();
 }
}
auto setup() -> void
{
 for (auto i = 0; i < Number_Of_Solenoid; ++i) {
   solenoiders[i].pin(Solenoid_Pins[i]);
   solenoiders[i].time(Solenoid_On_Time_in_MilliSeconds);
 }
  for (auto i = 0; i < Number_Of_Motor; ++i) {
    motors[i].pin(Motor_Pins[i]);
    motors[i].time(Motor_On_Time_in_MilliSeconds);
  }
 MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
 MsTimer2::set(1, tick1ms);
 MsTimer2::start();
};
auto getSolenoidIndex(const int noteNumber) -> int
{
 for (auto i = 0; i < Number_Of_Solenoid; ++i) {
   if (noteNumber == Solenoid_Midi_Notes[i]) {
     return i;
   }
 }
 return -1; // not found
};

auto getMotorIndex(const int noteNumber) -> int
{
 for (auto i = 0; i < Number_Of_Motor; ++i) {
   if (noteNumber == Motor_Midi_Notes[i]) {
     return i;
   }
 }
 return -1; // not found
};

auto loop() -> void
{
 if (!MIDI.read()) {
   return;
 }
 const auto type = MIDI.getType();
 const auto data1 = MIDI.getData1();
 const auto data2 = MIDI.getData2();
 const auto channel = MIDI.getChannel();
 if (type != midi::NoteOn) {
   return;
 }
 const auto solenoid_index = getSolenoidIndex(data1);
 if (solenoid_index != -1) {
  solenoiders[solenoid_index].activate();
 }

 const auto motor_index = getMotorIndex(data1);
 if (motor_index != -1) {
   motors[motor_index].activate();
 }

}