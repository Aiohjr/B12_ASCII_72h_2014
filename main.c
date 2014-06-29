#include <pdcurses.h>
#include "screen.h"
#include <time.h>
#include "maintypes.h"



void new_game()
{ 
 struct set mainset;
 gen_game();
 gen_set(&mainset,time(NULL)); 
 print_spoiler(&mainset); 
 getch();
}

void dummy_screen()
{
 erase();
 printw("Nope!");
 getch();
}


void main_menu()
{
int input;
noecho();
while (input!='e')
{
erase();
attron(COLOR_PAIR(2));printw("N");attroff(COLOR_PAIR(2));printw("ew game\n");
attron(COLOR_PAIR(2));printw("L");attroff(COLOR_PAIR(2));printw("oad game\n");
attron(COLOR_PAIR(2));printw("E");attroff(COLOR_PAIR(2));printw("xit\n");
input=getch();
switch(input)
 {
  case 'n':new_game();break;
  case 'l':dummy_screen();break;
  default:break;
 }
}

 
}

int main()
{
 initscr();
 start_color();
 getmaxyx(stdscr,scr_y,scr_x);
 init_pair(1,3,0);
 init_pair(2,4,0);
 init_pair(3,7,0);
 init_pair(4,2,0); 
 main_menu();
 
 return 0;
}