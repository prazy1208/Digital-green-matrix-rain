#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int random_no(int a, int b)
{
    return a + rand() % (b + 1);
}

int main(void)
{
   
    initscr();
    start_color(); 
    use_default_colors();
    init_pair(COLOR_GREEN, COLOR_GREEN, -1); 
    init_pair(COLOR_WHITE, COLOR_WHITE, -1); 

    int width, height;
    getmaxyx(stdscr, height, width);

    int matrix[height][width];
    memset(matrix, 0, sizeof(int) * height * width); 

    while (true) {
        for (int x = 0; x < width; x++) {
            for (int y = height - 1; y >= 0; y--) { 
                if (y != 0) { 
                    matrix[y][x] = matrix[y - 1][x]; 
                } else {
                    if (matrix[y][x]) { 
                        matrix[y][x]--; 
                    } else { 
                        if (random_no(1, 128) == 7) { 
                            matrix[y][x] = random_no(2, height);
                        }
                    }
                }
            }
        }

        for (int y = 0; y < height; y++) { 
            for (int x = 0; x < width; x++) { 
                if (matrix[y][x]) {
                    if (y != height - 1 && matrix[y + 1][x] == 0) { 
                        attron(COLOR_PAIR(COLOR_WHITE)); 
                    } else { 
                        attron(COLOR_PAIR(COLOR_GREEN)); 
                    }
                    mvaddch(y, x, random_no(33, 126));
                } else { 
                    mvaddch(y, x, ' '); 
                }
            }
            refresh(); 
            napms(1); 
        }
    }

    endwin();

    return 0;
}