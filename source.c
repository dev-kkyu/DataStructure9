#define _CRT_SECURE_NO_WARNINGS	//기본
#define size 19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StoneStack_ {
	int x;
	int y;
	int color;

	struct StoneStack_* next;
} StoneStack;

typedef struct contStone_ {
	char startx;
	char starty;
	char endx;
	char endy;
	char color;
	char length;
	char isempty;
} contStone;

void empty();
void black();
void white();
void specialblack();
void specialwhite();
void prt(int i, int j);		//i행 j열을 모양에 맞춰 출력
void boardprt();			//보드판 전체 출력
void set(StoneStack** mainsp, StoneStack** undosp);				//검은돌 흰돌 수 두기
void bwcount();				//보드판 전체의 흰돌과 검은돌의 각 개수 세기

void rc_cntstone();			//각 가로줄과 세로줄의 검은돌, 흰돌 갯수 출력
void maxcont_stone();		//각 가로, 세로줄에서 최대로 연속된 돌 출력
void maxcontdiag_stone();	//각 대각선에서 최대로 연속된 돌 출력

void specialreset();		//모양바꾼 바둑돌 원래상태로 돌리는거
contStone* maxcontview();			//모든 가로/세로/대각선에서 최대로 연속된 돌의 모양을 바꿈			//빈칸포함 최대연속돌의 좌표데이터 반환
void changeStone(contStone* data);		//연속돌 좌표 모양 바꿔주기
void prtcontStone(contStone* data);		//연속돌 좌표 출력

StoneStack Pop(StoneStack** sp);
void Push(StoneStack** sp, StoneStack data);
void Load(StoneStack** mainsp, StoneStack** undosp);
void Save(StoneStack* mainsp, StoneStack* undosp);
void Reset(StoneStack** sp);						//스택의 모든 데이터 삭제

int board[size][size];

int count, bcount, wcount;
int start = 1;

int main(void)
{
	StoneStack* Stone = NULL;
	StoneStack* Undo = NULL;
	while (start) {
		boardprt();
		set(&Stone, &Undo);
	}

	exit(0);
	return 0;
}


void empty() {
	printf("┼ ");
}

// 1은 블랙
void black() {
	printf("○");
}

// 2는 화이트
void white() {
	printf("●");
}

//특별블랙
void specialblack() {
	printf("♡");
}

//특별화이트
void specialwhite() {
	printf("♥");
}


void prt(int i, int j) {
	if (board[i][j] == 0)
		empty();
	else if (board[i][j] == 1)
		black();
	else if (board[i][j] == 2)
		white();
	else if (board[i][j] == 3)
		specialblack();
	else if (board[i][j] == 4)
		specialwhite();
	else
		printf("X");
}
void boardprt() {
	specialreset();
	changeStone(maxcontview());

	bwcount();

	printf("   0 1 2 3 4 5 6 7 8 9 101112131415161718\n");
	for (int i = 0; i < size; i++)
	{
		printf("%2d ", i);
		for (int j = 0; j < size; j++)
		{
			prt(i, j);
		}
		printf("\n");
	}
	printf("검은 돌 : %d개, 흰 돌 : %d개\n\n", bcount, wcount);
}

void set(StoneStack** mainsp, StoneStack** undosp) {
	while (1) {
		int order = 0;

		printf("-------------------------------------------------\n");
		printf("1 : 좌표 입력\n");
		printf("2 : 무르기/무르기취소\n");
		printf("3 : 게임 초기화\n");
		printf("4 : 이전 게임 불러오기\n");
		printf("5 : 저장하기\n");
		printf("6 : 저장 후 종료\n");
		printf("7 : 저장하지 않고 종료\n");
		printf("8 : 바둑판 정보 출력\n");
		printf("-------------------------------------------------\n");

		printf("메뉴를 선택해 주세요 : ");
		if (scanf("%d", &order) < 1) {
			printf("다시 입력해 주세요\n");
			while (getchar() != '\n');
			continue;
		}
		switch (order) {
		case 1:
			while (1) {
				int x, y;
				if (!(count % 2))
					printf("검은 ");
				else if (count % 2)
					printf("흰 ");
				printf("돌을 놓을 좌표를 입력하세요 (x y) : ");
				while (getchar() != '\n');
				if (scanf("%d %d", &x, &y) < 2) {
					printf("잘못된 입력입니다. 다시 입력해 주세요.\n\n");
					while (getchar() != '\n');
					continue;
				}
				if (x < 0 || x>18 || y < 0 || y>18) {
					printf("x, y의 범위는 0~18입니다. 다시 입력해 주세요.\n\n");
					continue;
				}
				if (board[x][y] != 0) {
					printf("이미 돌이 놓여져 있습니다. 다시 입력해 주세요.\n\n");
					continue;
				}

				if (!(count % 2)) {
					board[x][y] = 1;
					StoneStack temp = { x, y, 1, NULL };
					Push(mainsp, temp);
					Reset(undosp);
				}
				else if (count % 2) {
					board[x][y] = 2;
					StoneStack temp = { x, y, 2, NULL };
					Push(mainsp, temp);
					Reset(undosp);
				}
				break;
			}
			break;
		case 2:
			while (1) {
				char num;
				printf("U : 무르기 || R : 무르기 취소\n");
				printf("입력해 주세요 : ");
				while (getchar() != '\n');
				if (scanf("%c", &num) < 1) {
					printf("다시 입력해 주세요\n\n");
					continue;
				}
				switch (num) {
				case 'U': {
					StoneStack temp = Pop(mainsp);
					if (temp.x == -1) {
						printf("더 이상 무를 수 없습니다.\n");
						system("pause");
						break;
					}
					Push(undosp, temp);
					board[temp.x][temp.y] = 0;
					break; }
				case 'R': {
					StoneStack temp = Pop(undosp);
					if (temp.x == -1) {
						printf("무른 돌이 없습니다.\n");
						system("pause");
						break;
					}
					Push(mainsp, temp);
					board[temp.x][temp.y] = temp.color;
					break; }
				default:
					printf("다시 입력해 주세요\n\n");
					continue;
					break;
				}
				break;
			}
			break;
		case 3:
			Reset(mainsp);
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					board[i][j] = 0;
			Reset(undosp);
			break;
		case 4:
			Reset(mainsp);
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					board[i][j] = 0;
			Reset(undosp);
			Load(mainsp, undosp);
			break;
		case 5:
			Save(*mainsp, *undosp);
			break;
		case 6:
			Save(*mainsp, *undosp);
			start = 0;
			return;
		case 7:
			start = 0;
			return;
		case 8:
			system("cls");
			rc_cntstone();
			maxcont_stone();
			maxcontdiag_stone();
			prtcontStone(maxcontview());
			return;
		default:
			printf("다시 입력해 주세요\n");
			system("pause");
			break;
		}
		system("cls");
		break;
	}
}

void bwcount()
{
	bcount = 0;
	wcount = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == 1 || board[i][j] == 3)
				bcount++;
			else if (board[i][j] == 2 || board[i][j] == 4)
				wcount++;
		}
	}
	count = bcount + wcount;
}

void rc_cntstone()
{
	printf("-----------각 행과 열의 검은돌, 흰돌 개수-----------\n");
	int rowbtemp = 0, rowwtemp = 0, colbtemp = 0, colwtemp = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			switch (board[i][j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				rowbtemp++;
				break;
			case 2:
			case 4:
				rowwtemp++;
				break;
			}
		}
		for (int j = 0; j < size; j++) {
			switch (board[j][i]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				colbtemp++;
				break;
			case 2:
			case 4:
				colwtemp++;
				break;
			}
		}

		printf("%2d행 검은 돌 : %2d개, 흰 돌 : %2d개	| %2d열 검은 돌 : %2d개, 흰 돌 : %2d개\n", i, rowbtemp, rowwtemp, i, colbtemp, colwtemp);

		rowbtemp = 0; rowwtemp = 0; colbtemp = 0; colwtemp = 0;
	}
	printf("\n");
}

void maxcont_stone()
{
	printf("-----------각 행과 열에서 가장 많이 연속된 돌 출력-----------\n");
	int btemp = 1, wtemp = 1, rowb_max = 0, roww_max = 0, colb_max = 0, colw_max = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			switch (board[i][j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[i][j + 1] == 1 || board[i][j + 1] == 3) {
					btemp++;
					if (btemp > rowb_max)
						rowb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[i][j + 1] == 2 || board[i][j + 1] == 4) {
					wtemp++;
					if (wtemp > roww_max)
						roww_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		for (int j = 0; j < size - 1; j++) {
			switch (board[j][i]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][i] == 1 || board[j + 1][i] == 3) {
					btemp++;
					if (btemp > colb_max)
						colb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[j + 1][i] == 2 || board[j + 1][i] == 4) {
					wtemp++;
					if (wtemp > colw_max)
						colw_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		printf("%2d행 MAX : ", i);
		if (rowb_max > roww_max)
			printf("검정, %2d개		", rowb_max);
		else if (rowb_max < roww_max)
			printf("흰색, %2d개		", roww_max);
		else if (rowb_max == roww_max && rowb_max != 0)
			printf("[검정, 흰색], %2d개	", rowb_max);
		else
			printf("연속된 돌 없음	");

		printf("| %2d열 MAX : ", i);
		if (colb_max > colw_max)
			printf("검정, %2d개\n", colb_max);
		else if (colb_max < colw_max)
			printf("흰색, %2d개\n", colw_max);
		else if (colb_max == colw_max && colb_max != 0)
			printf("[검정, 흰색], %2d개\n", colb_max);
		else
			printf("연속된 돌 없음\n");


		rowb_max = 0; roww_max = 0; colb_max = 0; colw_max = 0; btemp = 1; wtemp = 1;
	}
	printf("\n");
}

void maxcontdiag_stone()
{
	printf("-----------각 대각선에서 가장 많이 연속된 돌 출력-----------\n");
	int btemp = 1, wtemp = 1, rowb_max = 0, roww_max = 0, colb_max = 0, colw_max = 0;


	printf("------------------------------------------------------------\n");
	printf("	(↘)방향 대각선.	행, 열은 대각선의 시작 위치\n");
	printf("	0행과 0열은 같은 대각선입니다.\n");
	printf("------------------------------------------------------------\n");

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < i; j++) {
			switch (board[size - 1 - i + j][j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[size - i + j][j + 1] == 1 || board[size - i + j][j + 1] == 3) {
					btemp++;
					if (btemp > rowb_max)
						rowb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[size - i + j][j + 1] == 2 || board[size - i + j][j + 1] == 4) {
					wtemp++;
					if (wtemp > roww_max)
						roww_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		for (int j = 0; j < size - i - 1; j++) {
			switch (board[j][j + i]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][j + i + 1] == 1 || board[j + 1][j + i + 1] == 3) {
					btemp++;
					if (btemp > colb_max)
						colb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[j + 1][j + i + 1] == 2 || board[j + 1][j + i + 1] == 4) {
					wtemp++;
					if (wtemp > colw_max)
						colw_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		printf("%2d행 MAX : ", size - 1 - i);
		if (rowb_max > roww_max)
			printf("검정, %2d개		", rowb_max);
		else if (rowb_max < roww_max)
			printf("흰색, %2d개		", roww_max);
		else if (rowb_max == roww_max && rowb_max != 0)
			printf("[검정, 흰색], %2d개	", rowb_max);
		else
			printf("연속된 돌 없음	");

		printf("| %2d열 MAX : ", i);
		if (colb_max > colw_max)
			printf("검정, %2d개\n", colb_max);
		else if (colb_max < colw_max)
			printf("흰색, %2d개\n", colw_max);
		else if (colb_max == colw_max && colb_max != 0)
			printf("[검정, 흰색], %2d개\n", colb_max);
		else
			printf("연속된 돌 없음\n");


		rowb_max = 0; roww_max = 0; colb_max = 0; colw_max = 0; btemp = 1; wtemp = 1;
	}



	printf("------------------------------------------------------------\n");
	printf("	(↙)방향 대각선.	행, 열은 대각선의 시작 위치\n");
	printf("	18열과 0행은 같은 대각선입니다.\n");
	printf("------------------------------------------------------------\n");

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i; j++) {
			switch (board[j][i - j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][i - j - 1] == 1 || board[j + 1][i - j - 1] == 3) {
					btemp++;
					if (btemp > rowb_max)
						rowb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[j + 1][i - j - 1] == 2 || board[j + 1][i - j - 1] == 4) {
					wtemp++;
					if (wtemp > roww_max)
						roww_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		for (int j = 0; j < size - i - 1; j++) {
			switch (board[i + j][size - 1 - j]) {
			case 0:
				continue;
				break;
			case 1:
			case 3:
				if (board[i + j + 1][size - 2 - j] == 1 || board[i + j + 1][size - 2 - j] == 3) {
					btemp++;
					if (btemp > colb_max)
						colb_max = btemp;
				}
				else
					btemp = 1;
				break;
			case 2:
			case 4:
				if (board[i + j + 1][size - 2 - j] == 2 || board[i + j + 1][size - 2 - j] == 4) {
					wtemp++;
					if (wtemp > colw_max)
						colw_max = wtemp;
				}
				else
					wtemp = 1;
				break;
			}
		}

		printf("%2d열 MAX : ", i);
		if (rowb_max > roww_max)
			printf("검정, %2d개		", rowb_max);
		else if (rowb_max < roww_max)
			printf("흰색, %2d개		", roww_max);
		else if (rowb_max == roww_max && rowb_max != 0)
			printf("[검정, 흰색], %2d개	", rowb_max);
		else
			printf("연속된 돌 없음	");

		printf("| %2d행 MAX : ", i);
		if (colb_max > colw_max)
			printf("검정, %2d개\n", colb_max);
		else if (colb_max < colw_max)
			printf("흰색, %2d개\n", colw_max);
		else if (colb_max == colw_max && colb_max != 0)
			printf("[검정, 흰색], %2d개\n", colb_max);
		else
			printf("연속된 돌 없음\n");


		rowb_max = 0; roww_max = 0; colb_max = 0; colw_max = 0; btemp = 1; wtemp = 1;
	}
	printf("\n");
}

void specialreset() {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (board[i][j] > 2)
				board[i][j] -= 2;
}

contStone* maxcontview()
{
	contStone Stonedata[100] = { 0 };
	int dataindex = 0;

	int max = 0;



	//가로줄
	contStone tempcontrow[50] = { 0 };
	int tempindex = 0;

	int temp = 1;

	for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 전체 가로줄에서 1개 이상 연속인 돌의 정보를 저장
		for (int j = 0; j < size - 1; j++) {
			switch (board[i][j]) {
			case 0:
				if (j == size - 2) {
					if (board[i][j + 1] == 1 || board[i][j + 1] == 3) {
						tempcontrow[tempindex].startx = i;
						tempcontrow[tempindex].starty = j - temp + 2;
						tempcontrow[tempindex].endx = i;
						tempcontrow[tempindex].endy = j + 1;
						tempcontrow[tempindex].color = 1;
						tempcontrow[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[i][j + 1] == 2 || board[i][j + 1] == 4) {
						tempcontrow[tempindex].startx = i;
						tempcontrow[tempindex].starty = j - temp + 2;
						tempcontrow[tempindex].endx = i;
						tempcontrow[tempindex].endy = j + 1;
						tempcontrow[tempindex].color = 2;
						tempcontrow[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[i][j + 1] == 1 || board[i][j + 1] == 3) {
					temp++;
					if (j == size - 2 && temp != 1) {
						tempcontrow[tempindex].startx = i;
						tempcontrow[tempindex].starty = j - temp + 2;
						tempcontrow[tempindex].endx = i;
						tempcontrow[tempindex].endy = j + 1;
						tempcontrow[tempindex].color = 1;
						tempcontrow[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontrow[tempindex].startx = i;
					tempcontrow[tempindex].starty = j - temp + 1;
					tempcontrow[tempindex].endx = i;
					tempcontrow[tempindex].endy = j;
					tempcontrow[tempindex].color = 1;
					tempcontrow[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[i][j + 1] == 2 || board[i][j + 1] == 4) {
					temp++;
					if (j == size - 2 && temp != 1) {
						tempcontrow[tempindex].startx = i;
						tempcontrow[tempindex].starty = j - temp + 2;
						tempcontrow[tempindex].endx = i;
						tempcontrow[tempindex].endy = j + 1;
						tempcontrow[tempindex].color = 2;
						tempcontrow[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontrow[tempindex].startx = i;
					tempcontrow[tempindex].starty = j - temp + 1;
					tempcontrow[tempindex].endx = i;
					tempcontrow[tempindex].endy = j;
					tempcontrow[tempindex].color = 2;
					tempcontrow[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontrow[i].length != 0; i++) {						//tempcontrow에 저장되어 있는 연속돌 중에서 length가 max인 값을 저장
		if (tempcontrow[i].length > max) {
			max = tempcontrow[i].length;
		}
	}

	for (int i = 0; tempcontrow[i + 1].length != 0; i++) {					//tempcontrow에 저장되어 있는 연속 돌 중에서 빈칸포함해서 max인 값 저장
		if (tempcontrow[i].endx == tempcontrow[i + 1].endx && tempcontrow[i].endy + 2 == tempcontrow[i + 1].starty && tempcontrow[i].color == tempcontrow[i + 1].color && board[tempcontrow[i].endx][tempcontrow[i].endy + 1] == 0)
			if (tempcontrow[i].length + tempcontrow[i + 1].length > max)
				max = tempcontrow[i].length + tempcontrow[i + 1].length;
	}












	//세로줄
	contStone tempcontcol[50] = { 0 };
	tempindex = 0;
	temp = 1;

	for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 전체 세로줄에서 1개 이상 연속인 돌의 정보를 저장
		for (int j = 0; j < size - 1; j++) {
			switch (board[j][i]) {
			case 0:
				if (j == size - 2) {
					if (board[j + 1][i] == 1 || board[j + 1][i] == 3) {
						tempcontcol[tempindex].startx = j - temp + 2;
						tempcontcol[tempindex].starty = i;
						tempcontcol[tempindex].endx = j + 1;
						tempcontcol[tempindex].endy = i;
						tempcontcol[tempindex].color = 1;
						tempcontcol[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[j + 1][i] == 2 || board[j + 1][i] == 4) {
						tempcontcol[tempindex].startx = j - temp + 2;
						tempcontcol[tempindex].starty = i;
						tempcontcol[tempindex].endx = j + 1;
						tempcontcol[tempindex].endy = i;
						tempcontcol[tempindex].color = 2;
						tempcontcol[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][i] == 1 || board[j + 1][i] == 3) {
					temp++;
					if (j == size - 2 && temp != 1) {
						tempcontcol[tempindex].startx = j - temp + 2;
						tempcontcol[tempindex].starty = i;
						tempcontcol[tempindex].endx = j + 1;
						tempcontcol[tempindex].endy = i;
						tempcontcol[tempindex].color = 1;
						tempcontcol[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontcol[tempindex].startx = j - temp + 1;
					tempcontcol[tempindex].starty = i;
					tempcontcol[tempindex].endx = j;
					tempcontcol[tempindex].endy = i;
					tempcontcol[tempindex].color = 1;
					tempcontcol[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[j + 1][i] == 2 || board[j + 1][i] == 4) {
					temp++;
					if (j == size - 2 && temp != 1) {
						tempcontcol[tempindex].startx = j - temp + 2;
						tempcontcol[tempindex].starty = i;
						tempcontcol[tempindex].endx = j + 1;
						tempcontcol[tempindex].endy = i;
						tempcontcol[tempindex].color = 2;
						tempcontcol[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontcol[tempindex].startx = j - temp + 1;
					tempcontcol[tempindex].starty = i;
					tempcontcol[tempindex].endx = j;
					tempcontcol[tempindex].endy = i;
					tempcontcol[tempindex].color = 2;
					tempcontcol[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontcol[i].length != 0; i++) {						//tempcontcol에 저장되어 있는 연속돌 중에서 length가 max인 값을 저장
		if (tempcontcol[i].length > max) {
			max = tempcontcol[i].length;
		}
	}

	for (int i = 0; tempcontcol[i + 1].length != 0; i++) {					//tempcontcol에 저장되어 있는 연속 돌 중에서 빈칸포함해서 max인 값 저장
		if (tempcontcol[i].endy == tempcontcol[i + 1].endy && tempcontcol[i].endx + 2 == tempcontcol[i + 1].startx && tempcontcol[i].color == tempcontcol[i + 1].color && board[tempcontcol[i].endx + 1][tempcontcol[i].endy] == 0)
			if (tempcontcol[i].length + tempcontcol[i + 1].length > max)
				max = tempcontcol[i].length + tempcontcol[i + 1].length;
	}




	//대각선1
	contStone tempcontdiag1[50] = { 0 };
	tempindex = 0;

	temp = 1;

	for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↘1 대각선에서 1개 이상 연속인 돌의 정보를 저장
		for (int j = 0; j < i; j++) {
			switch (board[size - 1 - i + j][j]) {
			case 0:
				if (j == i - 1) {
					if (board[size - 1 - i + j + 1][j + 1] == 1 || board[size - 1 - i + j + 1][j + 1] == 3) {
						tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 2;
						tempcontdiag1[tempindex].starty = j - temp + 2;
						tempcontdiag1[tempindex].endx = size - 1 - i + j + 1;
						tempcontdiag1[tempindex].endy = j + 1;
						tempcontdiag1[tempindex].color = 1;
						tempcontdiag1[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[size - 1 - i + j + 1][j + 1] == 2 || board[size - 1 - i + j + 1][j + 1] == 4) {
						tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 2;
						tempcontdiag1[tempindex].starty = j - temp + 2;
						tempcontdiag1[tempindex].endx = size - 1 - i + j + 1;
						tempcontdiag1[tempindex].endy = j + 1;
						tempcontdiag1[tempindex].color = 2;
						tempcontdiag1[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[size - i + j][j + 1] == 1 || board[size - i + j][j + 1] == 3) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 2;
						tempcontdiag1[tempindex].starty = j - temp + 2;
						tempcontdiag1[tempindex].endx = size - 1 - i + j + 1;
						tempcontdiag1[tempindex].endy = j + 1;
						tempcontdiag1[tempindex].color = 1;
						tempcontdiag1[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 1;
					tempcontdiag1[tempindex].starty = j - temp + 1;
					tempcontdiag1[tempindex].endx = size - 1 - i + j;
					tempcontdiag1[tempindex].endy = j;
					tempcontdiag1[tempindex].color = 1;
					tempcontdiag1[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[size - i + j][j + 1] == 2 || board[size - i + j][j + 1] == 4) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 2;
						tempcontdiag1[tempindex].starty = j - temp + 2;
						tempcontdiag1[tempindex].endx = size - 1 - i + j + 1;
						tempcontdiag1[tempindex].endy = j + 1;
						tempcontdiag1[tempindex].color = 2;
						tempcontdiag1[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag1[tempindex].startx = size - 1 - i + j - temp + 1;
					tempcontdiag1[tempindex].starty = j - temp + 1;
					tempcontdiag1[tempindex].endx = size - 1 - i + j;
					tempcontdiag1[tempindex].endy = j;
					tempcontdiag1[tempindex].color = 2;
					tempcontdiag1[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontdiag1[i].length != 0; i++) {						//tempcontdiag1에 저장되어 있는 연속돌 중에서 length가 max인 값을 저장
		if (tempcontdiag1[i].length > max) {
			max = tempcontdiag1[i].length;
		}
	}

	for (int i = 0; tempcontdiag1[i + 1].length != 0; i++) {					//tempcontdiag1에 저장되어 있는 연속 돌 중에서 빈칸포함해서 max인 값 저장
		if (tempcontdiag1[i].endx + 2 == tempcontdiag1[i + 1].startx && tempcontdiag1[i].endy + 2 == tempcontdiag1[i + 1].starty && tempcontdiag1[i].color == tempcontdiag1[i + 1].color && board[tempcontdiag1[i].endx + 1][tempcontdiag1[i].endy + 1] == 0)
			if (tempcontdiag1[i].length + tempcontdiag1[i + 1].length > max)
				max = tempcontdiag1[i].length + tempcontdiag1[i + 1].length;
	}


	//대각선2 하는중
	contStone tempcontdiag2[50] = { 0 };
	tempindex = 0;

	temp = 1;

	for (int i = 1; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↘2 대각선에서 1개 이상 연속인 돌의 정보를 저장
		for (int j = 0; j < size - 1 - i; j++) {
			switch (board[j][j + i]) {
			case 0:
				if (j == size - 2 - i) {
					if (board[j + 1][j + i + 1] == 1 || board[j + 1][j + i + 1] == 3) {
						tempcontdiag2[tempindex].startx = j - temp + 2;
						tempcontdiag2[tempindex].starty = j + i - temp + 2;
						tempcontdiag2[tempindex].endx = j;
						tempcontdiag2[tempindex].endy = j + i;
						tempcontdiag2[tempindex].color = 1;
						tempcontdiag2[tempindex++].length = temp;
						temp = 1;
					}
					else if (board[j + 1][j + i + 1] == 2 || board[j + 1][j + i + 1] == 4) {
						tempcontdiag2[tempindex].startx = j - temp + 2;
						tempcontdiag2[tempindex].starty = j + i - temp + 2;
						tempcontdiag2[tempindex].endx = j;
						tempcontdiag2[tempindex].endy = j + i;
						tempcontdiag2[tempindex].color = 2;
						tempcontdiag2[tempindex++].length = temp;
						temp = 1;
					}
				}
				continue;
				break;
			case 1:
			case 3:
				if (board[j + 1][j + i + 1] == 1 || board[j + 1][j + i + 1] == 3) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag2[tempindex].startx = j - temp + 2;
						tempcontdiag2[tempindex].starty = j + i - temp + 2;
						tempcontdiag2[tempindex].endx = j;
						tempcontdiag2[tempindex].endy = j + i;
						tempcontdiag2[tempindex].color = 1;
						tempcontdiag2[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag2[tempindex].startx = j - temp + 1;
					tempcontdiag2[tempindex].starty = j + i - temp + 1;
					tempcontdiag2[tempindex].endx = j;
					tempcontdiag2[tempindex].endy = j + i;
					tempcontdiag2[tempindex].color = 1;
					tempcontdiag2[tempindex++].length = temp;
					temp = 1;
				}
				break;
			case 2:
			case 4:
				if (board[j + 1][j + i + 1] == 2 || board[j + 1][j + i + 1] == 4) {
					temp++;
					if (j == i - 1 && temp != 1) {
						tempcontdiag2[tempindex].startx = j - temp + 2;
						tempcontdiag2[tempindex].starty = j + i - temp + 2;
						tempcontdiag2[tempindex].endx = j;
						tempcontdiag2[tempindex].endy = j + i;
						tempcontdiag2[tempindex].color = 2;
						tempcontdiag2[tempindex++].length = temp;
						temp = 1;
					}
				}
				else {
					tempcontdiag2[tempindex].startx = j - temp + 1;
					tempcontdiag2[tempindex].starty = j + i - temp + 1;
					tempcontdiag2[tempindex].endx = j;
					tempcontdiag2[tempindex].endy = j + i;
					tempcontdiag2[tempindex].color = 2;
					tempcontdiag2[tempindex++].length = temp;
					temp = 1;
				}
				break;
			}
		}
		temp = 1;
	}




	for (int i = 0; tempcontdiag2[i].length != 0; i++) {						//tempcontdiag2에 저장되어 있는 연속돌 중에서 length가 max인 값을 저장
		if (tempcontdiag2[i].length > max) {
			max = tempcontdiag2[i].length;
		}
	}

	for (int i = 0; tempcontdiag2[i + 1].length != 0; i++) {					//tempcontdiag2에 저장되어 있는 연속 돌 중에서 빈칸포함해서 max인 값 저장
		if (tempcontdiag2[i].endx + 2 == tempcontdiag2[i + 1].startx && tempcontdiag2[i].endy + 2 == tempcontdiag2[i + 1].starty && tempcontdiag2[i].color == tempcontdiag2[i + 1].color && board[tempcontdiag2[i].endx + 1][tempcontdiag2[i].endy + 1] == 0)
			if (tempcontdiag2[i].length + tempcontdiag2[i + 1].length > max)
				max = tempcontdiag2[i].length + tempcontdiag2[i + 1].length;
	}



















	if (max > 1) {
		for (int i = 0; tempcontrow[i].length != 0; i++) {						//tempcontrow에 저장되어 있는 연속 돌 중에서 length가 max인 데이터와 빈칸포함해서 max인 데이터 저장
			if (tempcontrow[i].length == max) {
				Stonedata[dataindex++] = tempcontrow[i];
			}
			else if (tempcontrow[i + 1].length == 0)
				break;
			else if (tempcontrow[i].endx == tempcontrow[i + 1].endx && tempcontrow[i].endy + 2 == tempcontrow[i + 1].starty && tempcontrow[i].color == tempcontrow[i + 1].color && board[tempcontrow[i].endx][tempcontrow[i].endy + 1] == 0 && tempcontrow[i].length + tempcontrow[i + 1].length == max) {
				Stonedata[dataindex].startx = tempcontrow[i].startx;
				Stonedata[dataindex].starty = tempcontrow[i].starty;
				Stonedata[dataindex].endx = tempcontrow[i].endx;
				Stonedata[dataindex].endy = tempcontrow[i + 1].endy;
				Stonedata[dataindex].color = tempcontrow[i].color;
				Stonedata[dataindex].length = tempcontrow[i].length + tempcontrow[i + 1].length;
				Stonedata[dataindex++].isempty = 1;
			}
		}
	}

	if (max > 1) {
		for (int i = 0; tempcontcol[i].length != 0; i++) {						//tempcontcol에 저장되어 있는 연속 돌 중에서 length가 max인 데이터와 빈칸포함해서 max인 데이터 저장
			if (tempcontcol[i].length == max) {
				Stonedata[dataindex++] = tempcontcol[i];
			}
			else if (tempcontcol[i + 1].length == 0)
				break;
			else if (tempcontcol[i].endy == tempcontcol[i + 1].endy && tempcontcol[i].endx + 2 == tempcontcol[i + 1].startx && tempcontcol[i].color == tempcontcol[i + 1].color && board[tempcontcol[i].endx + 1][tempcontcol[i].endy] == 0 && tempcontcol[i].length + tempcontcol[i + 1].length == max) {
				Stonedata[dataindex].startx = tempcontcol[i].startx;
				Stonedata[dataindex].starty = tempcontcol[i].starty;
				Stonedata[dataindex].endx = tempcontcol[i + 1].endx;
				Stonedata[dataindex].endy = tempcontcol[i].endy;
				Stonedata[dataindex].color = tempcontcol[i].color;
				Stonedata[dataindex].length = tempcontcol[i].length + tempcontcol[i + 1].length;
				Stonedata[dataindex++].isempty = 1;
			}
		}
	}

	if (max > 1) {
		for (int i = 0; tempcontdiag1[i].length != 0; i++) {						//tempcontdiag1에 저장되어 있는 연속 돌 중에서 length가 max인 데이터와 빈칸포함해서 max인 데이터 저장
			if (tempcontdiag1[i].length == max) {
				Stonedata[dataindex++] = tempcontdiag1[i];
			}
			else if (tempcontdiag1[i + 1].length == 0)
				break;
			else if (tempcontdiag1[i].endx + 2 == tempcontdiag1[i + 1].startx && tempcontdiag1[i].endy + 2 == tempcontdiag1[i + 1].starty && tempcontdiag1[i].color == tempcontdiag1[i + 1].color && board[tempcontdiag1[i].endx + 1][tempcontdiag1[i].endy + 1] == 0 && tempcontdiag1[i].length + tempcontdiag1[i + 1].length == max) {
				Stonedata[dataindex].startx = tempcontdiag1[i].startx;
				Stonedata[dataindex].starty = tempcontdiag1[i].starty;
				Stonedata[dataindex].endx = tempcontdiag1[i + 1].endx;
				Stonedata[dataindex].endy = tempcontdiag1[i + 1].endy;
				Stonedata[dataindex].color = tempcontdiag1[i].color;
				Stonedata[dataindex].length = tempcontdiag1[i].length + tempcontdiag1[i + 1].length;
				Stonedata[dataindex++].isempty = 1;
			}
		}
	}

	if (max > 1) {
		for (int i = 0; tempcontdiag2[i].length != 0; i++) {						//tempcontdiag2에 저장되어 있는 연속 돌 중에서 length가 max인 데이터와 빈칸포함해서 max인 데이터 저장
			if (tempcontdiag2[i].length == max) {
				Stonedata[dataindex++] = tempcontdiag2[i];
			}
			else if (tempcontdiag2[i + 1].length == 0)
				break;
			else if (tempcontdiag2[i].endx + 2 == tempcontdiag2[i + 1].startx && tempcontdiag2[i].endy + 2 == tempcontdiag2[i + 1].starty && tempcontdiag2[i].color == tempcontdiag2[i + 1].color && board[tempcontdiag2[i].endx + 1][tempcontdiag2[i].endy + 1] == 0 && tempcontdiag2[i].length + tempcontdiag2[i + 1].length == max) {
				Stonedata[dataindex].startx = tempcontdiag2[i].startx;
				Stonedata[dataindex].starty = tempcontdiag2[i].starty;
				Stonedata[dataindex].endx = tempcontdiag2[i + 1].endx;
				Stonedata[dataindex].endy = tempcontdiag2[i + 1].endy;
				Stonedata[dataindex].color = tempcontdiag2[i].color;
				Stonedata[dataindex].length = tempcontdiag2[i].length + tempcontdiag2[i + 1].length;
				Stonedata[dataindex++].isempty = 1;
			}
		}
	}


	return Stonedata;





	//int temp = 1, max = 0;


	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 전체 가로줄에서 연속된 돌의 최대값을 구해준다.
	//	for (int j = 0; j < size - 1; j++) {
	//		switch (board[i][j]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//			if (board[i][j + 1] == 1) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//			if (board[i][j + 1] == 2) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}

	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 전체 세로줄에서 연속된 돌의 최대값을 구해준다.
	//	for (int j = 0; j < size - 1; j++) {
	//		switch (board[j][i]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//			if (board[j + 1][i] == 1) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//			if (board[j + 1][i] == 2) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}

	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↘1대각선에서 연속된 돌의 최대값을 구해준다.
	//	for (int j = 0; j < i; j++) {
	//		switch (board[size - 1 - i + j][j]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//			if (board[size - i + j][j + 1] == 1) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//			if (board[size - i + j][j + 1] == 2) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}

	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↘2대각선에서 연속된 돌의 최대값을 구해준다.
	//	for (int j = 0; j < size - i - 1; j++) {
	//		switch (board[j][j + i]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//			if (board[j + 1][j + i + 1] == 1) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//			if (board[j + 1][j + i + 1] == 2) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}

	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↙1대각선에서 연속된 돌의 최대값을 구해준다.
	//	for (int j = 0; j < i; j++) {
	//		switch (board[j][i - j]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//			if (board[j + 1][i - j - 1] == 1) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//			if (board[j + 1][i - j - 1] == 2) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}

	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↙2대각선에서 연속된 돌의 최대값을 구해준다.
	//	for (int j = 0; j < size - i - 1; j++) {
	//		switch (board[i + j][size - 1 - j]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//			if (board[i + j + 1][size - 2 - j] == 1) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//			if (board[i + j + 1][size - 2 - j] == 2) {
	//				temp++;
	//				if (temp > max)
	//					max = temp;
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}


	//for (int i = 0; i < size; i++) {				//구한 최대값을 기반으로, 다시 한바퀴 돌면서 전체 가로에서 연속된 돌의 개수가 최대인것의 모양을 바꿔준다.
	//	for (int j = 0; j < size - 1; j++)
	//	{
	//		switch (board[i][j]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//		case 3:
	//			if (board[i][j + 1] == 1 || board[i][j + 1] == 3) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[i][j - max + 2 + k] == 0)
	//							;
	//						else if (board[i][j - max + 2 + k] < 3)
	//							board[i][j - max + 2 + k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//		case 4:
	//			if (board[i][j + 1] == 2 || board[i][j + 1] == 4) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[i][j - max + 2 + k] == 0)
	//							;
	//						else if (board[i][j - max + 2 + k] < 3)
	//							board[i][j - max + 2 + k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}

	//for (int i = 0; i < size; i++) {				//구한 최대값을 기반으로, 다시 한바퀴 돌면서 전체 세로에서 연속된 돌의 개수가 최대인것의 모양을 바꿔준다.
	//	for (int j = 0; j < size - 1; j++)
	//	{
	//		switch (board[j][i]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//		case 3:
	//			if (board[j + 1][i] == 1 || board[j + 1][i] == 3) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[j - max + 2 + k][i] == 0)
	//							;
	//						else if (board[j - max + 2 + k][i] < 3)
	//							board[j - max + 2 + k][i] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//		case 4:
	//			if (board[j + 1][i] == 2 || board[j + 1][i] == 4) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[j - max + 2 + k][i] == 0)
	//							;
	//						else if (board[j - max + 2 + k][i] < 3)
	//							board[j - max + 2 + k][i] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}



	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↘1대각선에서 연속된 돌의 모양변경
	//	for (int j = 0; j < i; j++) {
	//		switch (board[size - 1 - i + j][j]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//		case 3:
	//			if (board[size - i + j][j + 1] == 1 || board[size - i + j][j + 1] == 3) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[size - i + j - max + k + 1][j - max + 2 + k] == 0)
	//							;
	//						else if (board[size - i + j - max + k + 1][j - max + 2 + k] < 3)
	//							board[size - i + j - max + k + 1][j - max + 2 + k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;					
	//			break;
	//		case 2:
	//		case 4:
	//			if (board[size - i + j][j + 1] == 2 || board[size - i + j][j + 1] == 4){
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[size - i + j - max + k + 1][j - max + 2 + k] == 0)
	//							;
	//						else if (board[size - i + j - max + k + 1][j - max + 2 + k] < 3)
	//							board[size - i + j - max + k + 1][j - max + 2 + k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}

	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↘2대각선에서 연속된 돌의 모양변경
	//	for (int j = 0; j < size - i - 1; j++) {
	//		switch (board[j][j + i]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//		case 3:
	//			if (board[j + 1][j + i + 1] == 1 || board[j + 1][j + i + 1] == 3) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[j - max + 2 + k][i + j - max + 2 + k] == 0)
	//							;
	//						else if (board[j - max + 2 + k][i + j - max + 2 + k] < 3)
	//							board[j - max + 2 + k][i + j - max + 2 + k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//		case 4:
	//			if (board[j + 1][j + i + 1] == 2 || board[j + 1][j + i + 1] == 4) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[j - max + 2 + k][i + j - max + 2 + k] == 0)
	//							;
	//						else if (board[j - max + 2 + k][i + j - max + 2 + k] < 3)
	//							board[j - max + 2 + k][i + j - max + 2 + k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}

	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↙1대각선에서 연속된 돌의 모양변경
	//	for (int j = 0; j < i; j++) {
	//		switch (board[j][i - j]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//		case 3:
	//			if (board[j + 1][i - j - 1] == 1 || board[j + 1][i - j - 1] == 3) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[j - max + 2 + k][i - j + max - 2 - k] == 0)
	//							;
	//						else if (board[j - max + 2 + k][i - j + max - 2 - k] < 3)
	//							board[j - max + 2 + k][i - j + max - 2 - k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//		case 4:
	//			if (board[j + 1][i - j - 1] == 2 || board[j + 1][i - j - 1] == 4) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[j - max + 2 + k][i - j + max - 2 - k] == 0)
	//							;
	//						else if (board[j - max + 2 + k][i - j + max - 2 - k] < 3)
	//							board[j - max + 2 + k][i - j + max - 2 - k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}
	//
	//for (int i = 0; i < size; i++) {			//흰돌, 검은돌 상관 없이 ↙2대각선에서 연속된 돌의 모양변경
	//	for (int j = 0; j < size - i - 1; j++) {
	//		switch (board[i + j][size - 1 - j]) {
	//		case 0:
	//			continue;
	//			break;
	//		case 1:
	//		case 3:
	//			if (board[i + j + 1][size - 2 - j] == 1 || board[i + j + 1][size - 2 - j] == 3) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[i + j - max + 2 + k][size - 3 - j + max - k] == 0)
	//							;
	//						else if (board[i + j - max + 2 + k][size - 3 - j + max - k] < 3)
	//							board[i + j - max + 2 + k][size - 3 - j + max - k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		case 2:
	//		case 4:
	//			if (board[i + j + 1][size - 2 - j] == 2 || board[i + j + 1][size - 2 - j] == 4) {
	//				temp++;
	//				if (temp == max) {
	//					for (int k = 0; k < max; k++) {
	//						if (board[i + j - max + 2 + k][size - 3 - j + max - k] == 0)
	//							;
	//						else if (board[i + j - max + 2 + k][size - 3 - j + max - k] < 3)
	//							board[i + j - max + 2 + k][size - 3 - j + max - k] += 2;
	//					}
	//					temp = 1;
	//				}
	//			}
	//			else
	//				temp = 1;
	//			break;
	//		}
	//	}
	//	temp = 1;
	//}

}

void changeStone(contStone* data)
{
	for (int i = 0; data[i].length != 0; i++) {
		int x = data[i].startx;
		int y = data[i].starty;



		int menu = 0;
		int reallen = data[i].length + data[i].isempty;
		int temp1 = (data[i].endx - data[i].startx) / (reallen - 1);
		int temp2 = (data[i].endy - data[i].starty) / (reallen - 1);

		if (temp1 == 0 && temp2 == 1)
			menu = 1;							//가로
		else if (temp1 == 1 && temp2 == 0)
			menu = 2;							//세로
		else if (temp1 == 1 && temp2 == 1)
			menu = 3;							//↘대각선
		else if (temp1 == 1 && temp2 == -1)
			menu = 4;							//↙대각선


		switch (menu) {
		case 1:
			for (int j = 0; j < reallen; j++) {
				if (board[x][y + j] == 0)
					;
				else if (board[x][y + j] < 3)
					board[x][y + j] += 2;
			}
			break;

		case 2:
			for (int j = 0; j < reallen; j++) {
				if (board[x + j][y] == 0)
					;
				else if (board[x + j][y] < 3)
					board[x + j][y] += 2;
			}
			break;

		case 3:
			for (int j = 0; j < reallen; j++) {
				if (board[x + j][y + j] == 0)
					;
				else if (board[x + j][y + j] < 3)
					board[x + j][y + j] += 2;
			}
			break;


		default:
			break;
		}



	}
}

void prtcontStone(contStone* data)
{
	printf("--------------------최대 연속인 좌표 출력---------------------\n");
	for (int i = 0; data[i].length != 0; i++) {
		if (data[i].color == 1)
			printf("검은 돌 : ");
		else if (data[i].color == 2)
			printf("  흰 돌 : ");
		printf("( %2d, %2d ) ~ ( %2d, %2d )\n", data[i].startx, data[i].starty, data[i].endx, data[i].endy);
	}
	printf("\n");
}

StoneStack Pop(StoneStack** sp)
{
	if (*sp == NULL) {
		StoneStack temp = { -1, -1, -1, NULL };
		return temp;
	}

	StoneStack value = **sp;
	value.next = NULL;

	StoneStack* temp = *sp;

	*sp = (*sp)->next;

	free(temp);

	return value;
}

void Push(StoneStack** sp, StoneStack data)
{
	StoneStack* temp = (StoneStack*)malloc(sizeof(StoneStack));
	*temp = data;

	temp->next = *sp;
	*sp = temp;
}

void Load(StoneStack** mainsp, StoneStack** undosp)
{
	FILE* temp = fopen("data.txt", "a");
	fclose(temp);
	temp = fopen("undo.txt", "a");
	fclose(temp);

	StoneStack* tempStack1 = NULL;
	StoneStack* tempStack2 = NULL;

	temp = fopen("data.txt", "r");
	while (!feof(temp)) {
		StoneStack value = { -1, -1, -1, NULL };
		if (fscanf(temp, "%d, %d, %d\n", &value.x, &value.y, &value.color) < 3)
			break;
		Push(&tempStack1, value);
		board[value.x][value.y] = value.color;
	}
	fclose(temp);


	temp = fopen("undo.txt", "r");
	while (!feof(temp)) {
		StoneStack value = { -1, -1, -1, NULL };
		if (fscanf(temp, "%d, %d, %d\n", &value.x, &value.y, &value.color) < 3)
			break;
		Push(&tempStack2, value);
	}
	fclose(temp);

	while (1) {
		StoneStack tempValue = Pop(&tempStack1);
		if (tempValue.x == -1)
			break;
		Push(mainsp, tempValue);
	}

	while (1) {
		StoneStack tempValue = Pop(&tempStack2);
		if (tempValue.x == -1)
			break;
		Push(undosp, tempValue);
	}
}

void Save(StoneStack* mainsp, StoneStack* undosp)
{
	FILE* temp = fopen("data.txt", "w");

	for (StoneStack* p = mainsp; p != NULL; p = p->next) {
		fprintf(temp, "%d, %d, %d\n", p->x, p->y, p->color);
	}
	fclose(temp);

	temp = fopen("undo.txt", "w");

	for (StoneStack* p = undosp; p != NULL; p = p->next) {
		fprintf(temp, "%d, %d, %d\n", p->x, p->y, p->color);
	}
	fclose(temp);
}

void Reset(StoneStack** sp)
{
	while (1) {
		StoneStack temp = Pop(sp);
		if (temp.x == -1)
			break;
	}
}

