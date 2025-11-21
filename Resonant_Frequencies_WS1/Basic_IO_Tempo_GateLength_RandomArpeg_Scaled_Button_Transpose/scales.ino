#define CHROMATIC_NOTES 128


const int sChromaticNotes[CHROMATIC_NOTES] =

// Set the MIDI codes for the notes to be played
{
  0, 1, 2, 3, 4, 5, 6, 7, 8, //C-1 to G0
  9, 10, 11, 12,  13, 14, 15, 16, 17, 18, 19, 20, // A- to G#0
  21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, // A0 to G#1
  33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, // A1 to G#2
  45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, // A2 to G#3
  57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, // A3 to G#4
  69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, // A4 to G#5
  81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, // A5 to G#6
  93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, // A6 to G#7
  105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, // A7 to G#8
  117, 118, 119, 120 , 121, 122, 123, 124, 125, 126, 127 //A8 to D9
};



#define PENTATONIC_NOTES 54

// provides an index of pentatonic notes in the midi note table

const int sPentatonicNotes[PENTATONIC_NOTES] =
{
  0,   2,  4,  7,  9, 
  12, 14, 16, 19, 21, 
  24, 26, 28, 31, 33,
  36, 38, 40, 43, 45,
  48, 50, 52, 55, 57,
  60, 62, 64, 67, 69,
  72, 74, 76, 79, 81,
  84, 86, 88, 91, 93,
  96, 98,100,103,105,
 108,110,112,115,117,
 120,122,124,127 
};

#define CMBLUES_NOTES 65

// provides an index of pentatonic notes in the midi note table

const int sCMBluesNotes[CMBLUES_NOTES] =
{
  0,   3,  5,  6,  7, 10,  // 6
  12, 15, 17, 18, 19, 22,  // 12
  24, 27, 29, 30, 31, 34,  // 18
  36, 39, 41, 42, 43, 46,  // 24
  48, 51, 53, 54, 55, 58,  // 30
  60, 63, 65, 66, 67, 70,  // 36   
  72, 75, 77, 78, 79, 82,  // 42
  84, 87, 89, 90, 91, 94,  // 48
  96, 99,101,102,103,106,  // 54
 108,111,113,114,115,118,  // 60
 120,123,125,126,127       // 65
};


int setScale(int noteInput ,int scale, int transpose){

switch (scale)
{
  case 0:
  numNotesInScale = CHROMATIC_NOTES;
  playing = map(noteInput, 0, 127, 0, numNotesInScale - 1);
  return sChromaticNotes[playing + transpose];
  break;

  case 1:
  numNotesInScale = PENTATONIC_NOTES;
  playing = map(noteInput, 0, 127, 0, numNotesInScale - 1);
  return sPentatonicNotes[playing+ transpose];
  break;

  case 2:
  numNotesInScale = CMBLUES_NOTES;
  playing = map(noteInput, 0, 127, 0, numNotesInScale - 1);
  return sCMBluesNotes[playing + transpose];
  break;

  default:
  numNotesInScale = CHROMATIC_NOTES;
  playing = map(noteInput, 0, 127, 0, numNotesInScale - 1);
  return sChromaticNotes[playing + transpose];
  break;
}
}
