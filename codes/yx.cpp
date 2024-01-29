#include<cstdio>
#include<stdio.h>
#include<cstdlib>
#include<windows.h>
#include<conio.h> 
using namespace std;
char e[50][50]={"##############################",
				"#O         #   ##   # ### ####",
				"# ###### # # #    # # ### ####",
				"# #   ## #   # #### # ###   ##",
				"#   # ##  ###    #  #  ## ####",
				"##### #     # ##### ##    ####",
				"#   # ##### #   #   # # #    #",
				"# # #    ## # #### ## # # ####",
				"# # # ##      ##      # # ####",
				"# # # ####### ## ###### #   ##",
				"# #   ##   # ## ###### ###   #",
				"# ###### # #####  #        # #",
				"#        # #     ##### ### # @",
				"# ######## ##### # ### ### # #",
				"#     # ## ##### ###       ###",
				"##### # ## #      ######## # #",
				"#     # ## ## ###        #   #",
				"# # ###       ###### ####### #",
				"# #    ### ##      #         #",
				"##############################"};
void printmap(){
	system("cls");
	for(int i = 1;i <= 20;i++){
			printf("%s",e[i]);
		printf("\n");
	}
}
int main(){
	char ch;
	int tx,ty,x = 1,y = 1;
	printmap();
	while(e[x][y] != '@'){
		tx = x;ty = y;
		ch = getch();
		if(ch == 's'||ch == 'S'){
			tx = tx + 1;
			if(e[tx][ty] == ' '){
				e[tx - 1][ty] = ' ';
				e[tx][ty] = 'O';
				printmap();
				y = ty;x = tx;
			}
				else if(e[tx][ty] == '@')break;
		}
		tx = x;ty = y;
		if(ch == 'w'||ch == 'W'){
			tx = tx - 1;
			if(e[tx][ty] == ' '){
				e[tx + 1][ty] = ' ';
				e[tx][ty] = 'O';
				printmap();
				y = ty;x = tx;
			}	else if(e[tx][ty] == '@')break;
		}
		tx = x;ty = y;
		if(ch == 'a'||ch == 'A'){
			ty = ty - 1;
			if(e[tx][ty] == ' '){
				e[tx][ty + 1] = ' ';
				e[tx][ty] = 'O';
				printmap();
				x = tx;y = ty;
			}	else if(e[tx][ty] == '@')break;
		}
		tx = x;ty = y;
			if(ch == 'd'||ch == 'D'){
			ty = ty + 1;
			if(e[tx][ty] == ' '){
				e[tx][ty - 1] = ' ';
				e[tx][ty] = 'O';
				printmap();
				x = tx;y = ty;
			}	else if(e[tx][ty] == '@')break;
		}
	}
	system("cls");
	printf("You win.");
	return 0;
}
