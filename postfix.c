#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 // 스택의 최대 크기 = 10
#define MAX_EXPRESSION_SIZE 20 // 수식의 최대 크기 = 10

// stack 내에서 우선순위는 내림차순
// lparen = 0 가장 낮음
typedef enum{  // enum 타입으로 연산에 대한 우선순위 정의
	lparen = 0,  // ( 왼쪽 괄호 
	rparen = 9,  // ) 오른쪽 괄호
	times = 7,   // * 곱셈 
	divide = 6,  // / 나눗셈 
	plus = 5,    // + 덧셈 
	minus = 4,   // - 뺄셈 
	operand = 1 // 피연산자 
} precedence;

char infixExp[MAX_EXPRESSION_SIZE]; // 중위표기 저장 배열
char postfixExp[MAX_EXPRESSION_SIZE]; // 후위표기 저장 배열
char postfixStack[MAX_STACK_SIZE]; // 후기표기 변환을 위한 스택
int evalStack[MAX_STACK_SIZE]; // 계산을 위한 스택

int postfixStackTop = -1;
int evalStackTop = -1;
int evalResult = 0; // 계산 값 저장

void postfixPush(char x) // postfix 스택에 값 PUSH
{
    postfixStack[++postfixStackTop] = x; // x 값을 (Top + 1) 하여 PUSH
}

char postfixPop() // postfix 스택에 값 POP
{
	char x;
    if(postfixStackTop == -1) // Top = -1
        return '\0'; // NULL
    else {
    	x = postfixStack[postfixStackTop--]; // 스택 값을 x에 대입하여 (Top - 1) 하여 POP
    }
    return x;
}

void evalPush(int x) // eval 스택에 값 PUSH
{
    evalStack[++evalStackTop] = x; // x 값을 (Top + 1) 하여 PUSH
}

int evalPop() // eval 스택에 값 POP
{
    if(evalStackTop == -1) // Top = -1
        return -1;
    else
        return evalStack[evalStackTop--]; // Top 값 return 하고, (Top - 1)
}

// infix expression을 입력받는다.
// infixExp에는 입력된 값을 저장한다.
void getInfix() // 중위표기법 입력받기
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); // 수식 받기
}

precedence getToken(char symbol) // 수식 판단
{
	switch(symbol) {
	case '(' : return lparen; // ( : lparen 리턴
	case ')' : return rparen; // ) : rparen 리턴
	case '+' : return plus; // + : plus 리턴
	case '-' : return minus; // - : minus 리턴
	case '/' : return divide; // / : divide 리턴
	case '*' : return times; // * : times 리턴
	default : return operand; // 그 외 : operand 리턴
	}
}

precedence getPriority(char x) // 우선순위 판단
{
	return getToken(x); // getToken() 함수 호출
}

void charCat(char* c) // 문자하나를 전달받아, postfixExp에 추가
{
	if (postfixExp == '\0') // 배열이 NULL 일 경우
		strncpy(postfixExp, c, 1); // c 를 postfixExp에 복사
	else
		strncat(postfixExp, c, 1); // c 를 postfixExp에 이어붙이기
}

//infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
// 변경된 postfix는 postFixExp에 저장된다.

void toPostfix()
{
	char *exp = infixExp; // infixExp의 문자 하나씩을 읽기위한 포인터
	char x;

	// exp를 증가시켜가면서, 문자를 읽고 postfix로 변경
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand) // 피연산자일 경우
		{
			x = *exp;
        	charCat(&x);
		}
        else if(getPriority(*exp) == lparen) { // 왼쪽괄호 ( 일 경우

        	postfixPush(*exp); // infixExp 값을 후위표기 배열에 PUSH
        }
        else if(getPriority(*exp) == rparen) // 오른쪽괄호 ) 일 경우
        {
        	while((x = postfixPop()) != '(') { // 왼쪽괄호 ( 가 아닐 경우
        		charCat(&x);
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) 
            {
            	x = postfixPop(); // x 값을 후위표기 배열에 PUSH
            	charCat(&x);
            }
            postfixPush(*exp);
        }
        exp++;
	}

    while(postfixStackTop != -1) // postfix 배열 top 이 -1 이 아닐 경우
    {
    	x = postfixPop();
    	charCat(&x);
    }
}

void debug() // 디버그
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); // 중위표기 배열 출력
	printf("postExp =  %s\n", postfixExp); // 후위표기 배열 풀력
	printf("eval result = %d\n", evalResult); // 결과값 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++) 
		printf("%c  ", postfixStack[i]); // 원소 출력

	printf("\n");

}

void reset() // 초기화
{
	infixExp[0] = '\0'; // 중위표기 배열 인덱스[0] = NULL
	postfixExp[0] = '\0'; // 후위표기 배열 인덱스[0] = NULL

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; // 해당 인덱스[i] = NULL
         
	postfixStackTop = -1; // postfix top = -1 로 초기화
	evalStackTop = -1; // eval top = -1 로 초기화
	evalResult = 0; // 결과값을 0으로 초기화
}

void evaluation() //
{
	int opr1, opr2, i;
	int length = strlen(postfixExp);
	char symbol;
	evalStackTop = -1;

	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) { // 피연산자일 경우
			evalPush(symbol - '0'); // eval 스택에 (symbol - '0') PUSH
		}
		else { // 연산자일 경우
			opr2 = evalPop();
			opr1 = evalPop();
			switch(getToken(symbol)) {
			case plus: evalPush(opr1 + opr2); break; // 덧셈
			case minus: evalPush(opr1 - opr2); break; // 뺄셈
			case times: evalPush(opr1 * opr2); break; // 곱셈
			case divide: evalPush(opr1 / opr2); break; // 나눗셈
			default: break;
			}
		}
	}
	evalResult = evalPop(); // 결과값 출력
}

int main()
{
    printf("[----- [Kim Yun Seo]  [2020021016] -----]\n");

	char command; // command 변수

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 값 받기 

		switch(command) {
		case 'i': case 'I': // command 값이 i 또는 I 일 경우
			getInfix();
			break;
		case 'p': case 'P': // command 값이 p 또는 P 일 경우
			toPostfix();
			break;
		case 'e': case 'E': // command 값이 e 또는 E 일 경우
			evaluation();
			break;
		case 'd': case 'D': // command 값이 d 또는 D 일 경우
			debug();
			break;
		case 'r': case 'R': // command 값이 r 또는 R 일 경우
			reset();
			break;
		case 'q': case 'Q': // command 값이 q 또는 Q 일 경우
			break;
		default: // 기본값 (그 외)
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 입력받은 command 값이 q 또는 Q 이 아닐 경우 동안 진행

	return 1;
}
