// --- Day 6: Probably a Fire Hazard ---

// Because your neighbors keep defeating you in the holiday house decorating
// contest year after year, you've decided to deploy one million lights in a
// 1000x1000 grid.

// Furthermore, because you've been especially nice this year, Santa has mailed
// you instructions on how to display the ideal lighting configuration.

// Lights in your grid are numbered from 0 to 999 in each direction; the lights
// at each corner are at 0,0, 0,999, 999,999, and 999,0. The instructions
// include whether to turn on, turn off, or toggle various inclusive ranges
// given as coordinate pairs. Each coordinate pair represents opposite corners
// of a rectangle, inclusive; a coordinate pair like 0,0 through 2,2 therefore
// refers to 9 lights in a 3x3 square. The lights all start turned off.

// To defeat your neighbors this year, all you have to do is set up your lights
// by doing the instructions Santa sent you in order.

// For example:

//     turn on 0,0 through 999,999 would turn on (or leave on) every light.
//     toggle 0,0 through 999,0 would toggle the first line of 1000 lights,
//     turning off the ones that were on, and turning on the ones that were off.
//     turn off 499,499 through 500,500 would turn off (or leave off) the middle
//     four lights.

// After following the instructions, how many lights are lit?

// Your puzzle answer was 400410.

// The first half of this puzzle is complete! It provides one gold star: *
// --- Part Two ---

// You just finish implementing your winning light pattern when you realize you
// mistranslated Santa's message from Ancient Nordic Elvish.

// The light grid you bought actually has individual brightness controls; each
// light can have a brightness of zero or more. The lights all start at zero.

// The phrase turn on actually means that you should increase the brightness of
// those lights by 1.

// The phrase turn off actually means that you should decrease the brightness of
// those lights by 1, to a minimum of zero.

// The phrase toggle actually means that you should increase the brightness of
// those lights by 2.

// What is the total brightness of all lights combined after following Santa's
// instructions?

// For example:

//     turn on 0,0 through 0,0 would increase the total brightness by 1.
//     toggle 0,0 through 999,999 would increase the total brightness by
//     2000000.

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 50
#define GRID_SIZE 1000

int main(int argc, char *argv[]) {
  FILE *file;
  char line[MAX_LINE_LENGTH];
  int lights[GRID_SIZE][GRID_SIZE] = {0};
  int x1, y1, x2, y2; // start and end coordinates

  if (argc < 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error: cannot open file %s\n", argv[1]);
    return 1;
  }

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    unsigned int mode = 0; // 0 = off, 1 = on, 2 = toggle

    if (strstr(line, "turn on") != NULL) {
      mode = 1;
      sscanf(line, "turn on %d,%d through %d,%d", &x1, &y1, &x2, &y2);
    } else if (strstr(line, "turn off") != NULL) {
      mode = 0;
      sscanf(line, "turn off %d,%d through %d,%d", &x1, &y1, &x2, &y2);
    } else if (strstr(line, "toggle") != NULL) {
      mode = 2;
      sscanf(line, "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2);
    }

    // for (int i = x1; i <= x2; i++) {
    //   for (int j = y1; j <= y2; j++) {
    //     if (mode == 0) {
    //       lights[i][j] = 0;
    //     } else if (mode == 1) {
    //       lights[i][j] = 1;
    //     } else if (mode == 2) {
    //       lights[i][j] = !lights[i][j];
    //     }
    //   }
    // }

    for (int i = x1; i <= x2; i++) {
      for (int j = y1; j <= y2; j++) {
        if (mode == 0) {
          if (lights[i][j] > 0) {
            lights[i][j]--;
          }
        } else if (mode == 1) {
          lights[i][j]++;
        } else if (mode == 2) {
          lights[i][j] += 2;
        }
      }
    }
  }

  fclose(file);

  // int litLights = 0;
  // for (int i = 0; i < GRID_SIZE; i++) {
  //   for (int j = 0; j < GRID_SIZE; j++) {
  //     if (lights[i][j]) {
  //       litLights++;
  //     }
  //   }
  // }

  // printf("Lit lights: %d\n", litLights);

  int totalBrightness = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      totalBrightness += lights[i][j];
    }
  }

  printf("Total brightness: %d\n", totalBrightness);

  return 0;
}
