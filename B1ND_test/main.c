#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

char window[10] = { "윈도우팀" }, server[10] = { "서버팀" }, web[10] = { "웹팀" }, mobile[10] = { "모바일팀" };

char* depart(int n) {
	switch (n) {
	case 1:
		return window;
	case 2:
		return server;
	case 3:
		return web;
	case 4:
		return mobile;
	}
}

reg(FILE* lfp) {	//팀원 등록
	int n, dep;
	char name[10];
	printf("※ 팀원 등록 ※\n\n식별번호(무조건 양수), 이름, 부서번호 순으로 입력해주세요.\n\n");
	printf("1. 윈도우팀\n2. 서버팀\n3. 웹팀\n4. 모바일팀\n\n> ");
	scanf("%d %s %d", &n, name, &dep);
	if (dep > 4) {	//부서번호가 존재하지 않으면 오류 출력
		printf("\nERROR!\n부서번호가 잘못되었습니다.\n");
		printf("\n\n");
		system("pause");
		system("cls");
		reg(lfp);
	}
	else {
		fprintf(lfp, "%d %s %d ", n, name, dep);
		printf("\nSUCCESS!\n등록을 완료했습니다.\n");
		printf("\n\n");
		system("pause");
		fclose(lfp);
		system("cls");
	}
}

a_inq(FILE* lfp) {	//B1ND 전체 팀원 조회
	int n = -1, dep;
	char name[10];
	printf("※ B1ND 전체 팀원 조회 ※\n\n");
	printf("번호\t이름\t부서\n");
	while (1) {
		if (feof(lfp))
			break;
		fscanf(lfp, "%d %s %d ", &n, name, &dep);
		if (n < 0)	//팀원 목록이 존재할 때만 동작
			break;
		printf("%d\t%s\t%s\n", n, name, depart(dep));
	}
	printf("\n\n");
	system("pause");
	fclose(lfp);
	system("cls");
}

s_inq(FILE* lfp) {	//특정 팀원 조회
	int n1, n2, dep;
	char name[10];
	printf("※ 특정 팀원 조회 ※\n\n식별번호를 입력해주세요.\n\n> ");
	scanf("%d", &n1);
	while (1) {
		if (feof(lfp)) {	//파일의 끝까지 입력받아도 일치하는 번호가 없을 시 오류 출력
			printf("\nERROR!\n결과가 없습니다.\n");
			break;
		}
		fscanf(lfp, "%d %s %d ", &n2, name, &dep);
		if (n2 == n1) {	//입력받은 번호와 식별번호가 일치하면 이름과 부서 출력
			printf("\n이름\t부서\n%s\t%s\n", name, depart(dep));
			break;
		}
	}
	printf("\n\n");
	system("pause");
	fclose(lfp);
	system("cls");
}

move(FILE* lfp) {	//팀원 부서 이동
	int n1, n2 = -1, c = 0, dep, c_dep;
	char name[10];
	printf("※ 팀원 부서 이동 ※\n\n식별번호와 변경할 부서번호를 입력해주세요.\n\n");
	printf("1. 윈도우팀\n2. 서버팀\n3. 웹팀\n4. 모바일팀\n\n> ");
	scanf("%d %d", &n1, &c_dep);
	if (c_dep > 4) {	//부서번호가 존재하지 않으면 오류 출력
		printf("\nERROR!\n부서번호가 잘못되었습니다.\n");
		printf("\n\n");
		system("pause");
		system("cls");
		move(lfp);
	}
	else {
		FILE* ltp = fopen("list.tmp", "w");
		while (1) {
			if (feof(lfp))
				break;
			fscanf(lfp, "%d %s %d ", &n2, name, &dep);
			if (n2 < 0)	//팀원 목록이 존재할 때만 동작
				break;
			if (n2 == n1) {	//입력받은 번호와 식별번호가 일치하면 이름과 변경된 부서를 list.tmp에 출력
				fprintf(ltp, "%d %s %d ", n2, name, c_dep);
				c = 1;
			}
			else	//입력받은 이름과 부서를 list.tmp에 그대로 출력
				fprintf(ltp, "%d %s %d ", n2, name, dep);
		}
		if (c == 1)	//일치하는 번호가 있을 시 성공 메시지 출력
			printf("\nSUCCESS!\n이동을 완료했습니다.\n");
		else
			printf("\nERROR!\n이동할 대상이 없습니다.\n");
		printf("\n\n");
		system("pause");
		fclose(lfp);
		fclose(ltp);
		remove("list.txt");
		rename("list.tmp", "list.txt");
		system("cls");
	}
}

del(FILE* lfp) {	//팀원 삭제
	FILE* ltp = fopen("list.tmp", "w");
	int n1, n2 = -1, c = 0, dep;
	char name[10];
	printf("※ 팀원 삭제 ※\n\n삭제할 팀원의 식별번호를 입력해주세요.\n\n> ");
	scanf("%d", &n1);
	while (1) {
		if (feof(lfp))
			break;
		fscanf(lfp, "%d %s %d ", &n2, name, &dep);
		if (n2 < 0)	//팀원 목록이 존재할 때만 동작
			break;
		if (n2 != n1)	//입력받은 번호가 아니면 이름과 부서를 list.tmp에 출력
			fprintf(ltp, "%d %s %d ", n2, name, dep);
		else
			c = 1;
	}
	if (c == 1)	//일치하는 번호가 있을 시 성공 메시지 출력
		printf("\nSUCCESS!\n삭제를 완료했습니다.\n");
	else
		printf("\nERROR!\n삭제할 대상이 없습니다.\n");
	printf("\n\n");
	system("pause");
	fclose(lfp);
	fclose(ltp);
	remove("list.txt");
	rename("list.tmp", "list.txt");
	system("cls");
}

int main() {
	int n, con;
	char c;
	system("title B1ND 팀원 관리 프로그램");	//콘솔 이름
	system("color 0b");	//콘솔 색상
	//왜 민트색이냐구요? 민트초코는 맛있거든요.
	
	while (1) {
		FILE* lfp = fopen("list.txt", "a+");
		printf("\t※ B1ND 팀원 관리 ※\n\n");
		printf("\t\t\tMade by. Hermes\n\n");
		printf("_______________________________________\n\n");
		printf("1. 팀원 등록\n2. B1ND 전체 팀원 조회\n3. 특정 팀원 조회\n4. 팀원 부서 이동\n5. 팀원 삭제\n6. 목록 초기화\n7. 종료\n");
		printf("_______________________________________\n\n> ");
		scanf("%d", &n);
		system("cls");

		switch (n) {
		case 1:
			reg(lfp);
			break;
		case 2:
			a_inq(lfp);
			break;
		case 3:
			s_inq(lfp);
			break;
		case 4:
			move(lfp);
			break;
		case 5:
			del(lfp);
			break;
		case 6:
			printf("정말로 초기화하시겠습니까? (Y/N)\n\n> ");
			scanf(" %c", &c);
			if (c == 'Y') {
				fclose(lfp);
				con = remove("list.txt");
				if (con == 0)	//파일 삭제 중 오류가 없을 때 성공 메시지 출력
					printf("\nSUCCESS!\n초기화가 완료되었습니다.\n");
				else
					printf("\nERROR!\n무언가 잘못되었습니다.\n");
			}
			else if (c != 'N')	//입력값이 Y 또는 N이 아닐 때 오류 메시지 출력
				printf("\nERROR!\n잘못 입력되었습니다.\n");
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		case 7:
			fclose(lfp);
			exit(1);
		default:
			printf("ERROR!\n올바른 번호를 입력해주세요.\n\n");
			system("pause");
			fclose(lfp);
			system("cls");
		}
	}

	return 0;
}