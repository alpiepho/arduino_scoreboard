
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// gcc scoreboard.c -o runme ; ./runme

// C version to test ideas faster without loading on Arduino

#define C_APP
//#define INO_APP

//setup
// - turn all leds off
// - set counts A,B and (if double sided) C,D to "00 00"
// - set count A brigher indicating side (serving)

#define LEDS_PER_ROW 15
#define LED_ROWS 5
#define LED_SIDES 2

#define TOP_RIGHT 0
#define COLS (2*15)
#define ROWS 5
#define SIDES 2
#define DIGIT_WIDTH 3
#define DIGIT_GAP 0
#define SCORE_GAP 3

bool sideA = true;
int scoreA = 0;
int scoreB = 0;
int op = ' ';
bool running = true;
int table[ROWS][COLS];
int digitLedsA[ROWS][DIGIT_WIDTH];
int digitLedsB[ROWS][DIGIT_WIDTH];
int digitLedsC[ROWS][DIGIT_WIDTH];
int digitLedsD[ROWS][DIGIT_WIDTH];
int digitA[ROWS][DIGIT_WIDTH];
int digitB[ROWS][DIGIT_WIDTH];
int digitC[ROWS][DIGIT_WIDTH];
int digitD[ROWS][DIGIT_WIDTH];
#if SIDES == 2
int digitLedsE[ROWS][DIGIT_WIDTH];
int digitLedsF[ROWS][DIGIT_WIDTH];
int digitLedsG[ROWS][DIGIT_WIDTH];
int digitLedsH[ROWS][DIGIT_WIDTH];
int digitE[ROWS][DIGIT_WIDTH];
int digitF[ROWS][DIGIT_WIDTH];
int digitG[ROWS][DIGIT_WIDTH];
int digitH[ROWS][DIGIT_WIDTH];
#endif


#ifdef C_APP
void usage() {
    printf("options\n");
    printf("  r - reset scores\n");
    printf("  s - side-active change\n");
    printf("  p - add to side-active score\n");
    printf("  m - subtract to side-active score\n");
}
#endif

void get_op() {
#ifdef C_APP
    printf("option: ");
    op = getchar();
#endif
}

void clr_op() {
#ifdef C_APP
    getchar();
#endif
}

void clearDigit(int digit[ROWS][DIGIT_WIDTH], int val) {
    int i,j;
    for (i=0; i < ROWS; i++) {
        for (j=0; j < DIGIT_WIDTH; j++) {
            digit[i][j] = val;
        }     
    }
}

void clearDigitLeds() {
    clearDigit(digitLedsA, -1);
    clearDigit(digitLedsB, -1);
    clearDigit(digitLedsC, -1);
    clearDigit(digitLedsD, -1);
#if SIDES == 2
    clearDigit(digitLedsE, -1);
    clearDigit(digitLedsF, -1);
    clearDigit(digitLedsG, -1);
    clearDigit(digitLedsH, -1);
#endif
}

void clearDigits() {
    clearDigit(digitA, 0);
    clearDigit(digitB, 0);
    clearDigit(digitC, 0);
    clearDigit(digitD, 0);
#if SIDES == 2
    clearDigit(digitE, 0);
    clearDigit(digitF, 0);
    clearDigit(digitG, 0);
    clearDigit(digitH, 0);
#endif //SIDES == 2
}

void setupDigitLeds() {
    int i, side, cols, col, row, index;

    // set columns
    cols = SIDES * (4*DIGIT_WIDTH + 2*DIGIT_GAP + SCORE_GAP);

#if TOP_RIGHT == 1
    // start top,left
    index = 0;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        for (side = 0; side < SIDES; side++) {
            if (side == 0) {
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsA[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsB[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<SCORE_GAP; i++) {
                    col++;
                    index++;
            }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsC[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsD[row][i] = index;
                    col++;
                    index++;
                }
            }
#if SIDES == 2
            if (side == 1) {
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsE[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsF[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<SCORE_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsG[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsH[row][i] = index;
                    col++;
                    index++;
                }
            }
#endif //SIDES == 2
        }
    }
#endif // TOP_RIGHT=1


#if TOP_RIGHT == 0
    // start bottom,right
    index = (ROWS * COLS) -1;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        for (side = 0; side < SIDES; side++) {
            if (side == 0) {
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsA[row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsB[row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<SCORE_GAP; i++) {
                    col++;
                    index--;
            }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsC[row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsD[row][i] = index;
                    col++;
                    index--;
                }
            }
#if SIDES == 2
            if (side == 1) {
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsE[row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsF[row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<SCORE_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsG[row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsH[row][i] = index;
                    col++;
                    index--;
                }
            }
#endif //SIDES == 2
        }
    }
#endif // TOP_RIGHT=1
 
}


#ifdef C_APP

void print_table() {
    int i, side, cols, col, row, index;

    // verify columns
    cols = SIDES * (4*DIGIT_WIDTH + 2*DIGIT_GAP + SCORE_GAP);
    if (cols != COLS) {
        printf("WARNING: estimated col (%d) != COL (%d)\n", cols, COLS);
    }

#if TOP_RIGHT == 1
    // start top,left
    printf("int table[%d][%d] = [\n", ROWS, COLS);
    index = 0;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        printf("  [ ");
        for (side = 0; side < SIDES; side++) {
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index++;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf(" ");
                col++;
                index++;
            }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index++;
            }
            for (i=0; i<SCORE_GAP; i++) {
                printf(" ");
                col++;
                index++;
           }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index++;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf(" ");
                col++;
                index++;
            }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d", index);
                if ((col+1) < COLS) printf(", ");
                else                  printf(" ");
                col++;
                index++;
            }
            if ((side+1) < SIDES) printf("     ");
        }
        printf("]");
        if ((row+1) < ROWS) printf(",");
        printf("\n");
    }
    printf("];\n");
#endif // TOP_RIGHT=1


#if TOP_RIGHT == 0
    // start bottom,right
    printf("int table[%d][%d] = [\n", ROWS, COLS);
    index = (ROWS * COLS) -1;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        printf("  [ ");
        for (side = 0; side < SIDES; side++) {
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index--;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf(" ");
                col++;
                index--;
            }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index--;
            }
            for (i=0; i<SCORE_GAP; i++) {
                printf(" ");
                col++;
                index--;
           }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index--;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf(" ");
                col++;
                index--;
            }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d", index);
                if ((col+1) < COLS) printf(", ");
                else                  printf(" ");
                col++;
                index--;
            }
            if ((side+1) < SIDES) printf("     ");
        }
        printf("]");
        if ((row+1) < ROWS) printf(",");
        printf("\n");
    }
    printf("];\n");
#endif // TOP_RIGHT=1
}

void dumpDigitLine(int digit[ROWS][DIGIT_WIDTH], int row, char *post) {
    int col;
    for (col=0; col < DIGIT_WIDTH; col++) {
        printf("%3d ", digit[row][col]);
    } 
    printf("%s", post);
}

void dumpDigitLeds() {
    int row,j;
    for (row=0; row < ROWS; row++) {
        dumpDigitLine(digitLedsA, row, " ");
        dumpDigitLine(digitLedsB, row, "    ");
        dumpDigitLine(digitLedsC, row, " ");
#if SIDES == 1
        dumpDigitLine(digitLedsD, row, "\n");
#endif
#if SIDES == 2
        dumpDigitLine(digitLedsD, row, "  ...  ");
        dumpDigitLine(digitLedsE, row, " ");
        dumpDigitLine(digitLedsF, row, "    ");
        dumpDigitLine(digitLedsG, row, " ");
        dumpDigitLine(digitLedsH, row, "\n");
#endif  
    }
    printf("\n");
}

void dumpDigits() {
    int row,j;
    for (row=0; row < ROWS; row++) {
        dumpDigitLine(digitA, row, " ");
        dumpDigitLine(digitB, row, "    ");
        dumpDigitLine(digitC, row, " ");
#if SIDES == 1
        dumpDigitLine(digitD, row, "\n");
#endif
#if SIDES == 2
        dumpDigitLine(digitD, row, "  ...  ");
        dumpDigitLine(digitE, row, " ");
        dumpDigitLine(digitF, row, "    ");
        dumpDigitLine(digitG, row, " ");
        dumpDigitLine(digitH, row, "\n");
#endif  
    }
    printf("\n");
}


void print_txt() {
    printf("%s %02d  %02d %s\n", 
        (sideA ? ">" : " "),
        scoreA,
        scoreB,
        (sideA ? " " : "<")
    );
}

#endif // C_APP




void setup() {
    clearDigits();
    clearDigitLeds();
    setupDigitLeds();
}

void loop() {
    get_op();
    switch (op) {
        case 'r':
            scoreA = 0;
            scoreB = 0;
            break;
        case 's':
            sideA = !sideA;
            break;
        case 'p':
            if (sideA) { scoreA += 1; }
            else       { scoreB += 1; }
            break;
        case 'm':
            if (sideA) { scoreA -= 1; }
            else       { scoreB -= 1; }
            if (scoreA < 0) { scoreA = 0; }
            if (scoreB < 0) { scoreB = 0; }
#ifdef C_APP
        case '?' :
        case 'h' :
            usage();
            break;
        case 'q' :
            running = false;
            break;
        case 't':
            print_table();
            dumpDigitLeds();
            break;
#endif //C_APP
    }
    clr_op();
#ifdef C_APP
    print_txt();
    dumpDigits();
#endif //C_APP
}

//////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////
int main(void) {

    setup();

    while (running) {
        loop();
    }
    return 0;
}