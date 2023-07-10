*	Preamble
0:	LD 6,0(0)
1:	LDC 0,2(0)
2:	SUB 5,6,0
3:	SUB 4,6,0
4:	LDC 0,0(0)
*	
*	Assignment
5:	LDC 0,0(0)
6:	ST 0,0(6)
*	
*	whileLoop
7:	LD 0,0(6)
*	Push to stack
8:	ST 0,0(4)
9:	LDC 0,1(0)
10:	SUB 4,4,0
11:	LDC 1,3(0)
*	Push to stack
12:	ST 1,0(4)
13:	LDC 0,1(0)
14:	SUB 4,4,0
*	Pop from stack
15:	LDC 0,1(0)
16:	ADD 4,4,0
17:	LD 1,0(4)
*	Pop from stack
18:	LDC 0,1(0)
19:	ADD 4,4,0
20:	LD 0,0(4)
21:	SUB 0,0,1
*	
*	Assignment
23:	LD 0,0(6)
24:	LD 1,0(6)
*	Doing an Operation
25:	MUL 0,0,1
*	Push to stack
26:	ST 0,0(4)
27:	LDC 0,1(0)
28:	SUB 4,4,0
*	Pop from stack
29:	LDC 0,1(0)
30:	ADD 4,4,0
31:	LD 0,0(4)
32:	LD 1,0(6)
*	Doing an Operation
33:	MUL 0,0,1
*	Push to stack
34:	ST 0,0(4)
35:	LDC 0,1(0)
36:	SUB 4,4,0
37:	LDC 0,3(0)
38:	LD 1,0(6)
*	Doing an Operation
39:	MUL 0,0,1
*	Push to stack
40:	ST 0,0(4)
41:	LDC 0,1(0)
42:	SUB 4,4,0
*	Pop from stack
43:	LDC 0,1(0)
44:	ADD 4,4,0
45:	LD 0,0(4)
46:	LD 1,0(6)
*	Doing an Operation
47:	MUL 0,0,1
*	Push to stack
48:	ST 0,0(4)
49:	LDC 0,1(0)
50:	SUB 4,4,0
*	Pop from stack
51:	LDC 0,1(0)
52:	ADD 4,4,0
53:	LD 0,0(4)
*	Pop from stack
54:	LDC 0,1(0)
55:	ADD 4,4,0
56:	LD 1,0(4)
*	Doing an Operation
57:	ADD 0,0,1
*	Push to stack
58:	ST 0,0(4)
59:	LDC 0,1(0)
60:	SUB 4,4,0
61:	LDC 0,3(0)
62:	LD 1,0(6)
*	Doing an Operation
63:	MUL 0,0,1
*	Push to stack
64:	ST 0,0(4)
65:	LDC 0,1(0)
66:	SUB 4,4,0
*	Pop from stack
67:	LDC 0,1(0)
68:	ADD 4,4,0
69:	LD 0,0(4)
*	Pop from stack
70:	LDC 0,1(0)
71:	ADD 4,4,0
72:	LD 1,0(4)
*	Doing an Operation
73:	ADD 0,0,1
*	Push to stack
74:	ST 0,0(4)
75:	LDC 0,1(0)
76:	SUB 4,4,0
*	Pop from stack
77:	LDC 0,1(0)
78:	ADD 4,4,0
79:	LD 0,0(4)
80:	LDC 1,1(0)
*	Doing an Operation
81:	ADD 0,0,1
*	Push to stack
82:	ST 0,0(4)
83:	LDC 0,1(0)
84:	SUB 4,4,0
*	Pop from stack
85:	LDC 0,1(0)
86:	ADD 4,4,0
87:	LD 0,0(4)
*	Doing an Operation
*	Push to stack
88:	ST 0,0(4)
89:	LDC 0,1(0)
90:	SUB 4,4,0
*	Pop from stack
91:	LDC 0,1(0)
92:	ADD 4,4,0
93:	LD 0,0(4)
94:	ST 0,-1(6)
*	
*	Output
95:	LD 0,-1(6)
96:	OUT 0,0,0
*	
*	Assignment
97:	LD 0,0(6)
98:	LDC 1,1(0)
*	Doing an Operation
99:	ADD 0,0,1
*	Push to stack
100:	ST 0,0(4)
101:	LDC 0,1(0)
102:	SUB 4,4,0
*	Pop from stack
103:	LDC 0,1(0)
104:	ADD 4,4,0
105:	LD 0,0(4)
*	Doing an Operation
*	Push to stack
106:	ST 0,0(4)
107:	LDC 0,1(0)
108:	SUB 4,4,0
*	Pop from stack
109:	LDC 0,1(0)
110:	ADD 4,4,0
111:	LD 0,0(4)
112:	ST 0,0(6)
113:	LD 0,0(6)
*	Push to stack
114:	ST 0,0(4)
115:	LDC 0,1(0)
116:	SUB 4,4,0
117:	LDC 1,3(0)
*	Push to stack
118:	ST 1,0(4)
119:	LDC 0,1(0)
120:	SUB 4,4,0
*	Pop from stack
121:	LDC 0,1(0)
122:	ADD 4,4,0
123:	LD 1,0(4)
*	Pop from stack
124:	LDC 0,1(0)
125:	ADD 4,4,0
126:	LD 0,0(4)
127:	SUB 0,0,1
*	While loop jump
128:	LDC 7,22(0)
22:	JGE 0,129(7)
*	
*	Halt
129:	HALT 0,0,0
