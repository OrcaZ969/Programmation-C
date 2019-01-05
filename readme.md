# CProgrammation C

[TOC]

## Part 1

Compilation, structures de contrôle, opérations sur les types, opérations bits-à-bits

### Types entiers, casts, et promotion

Before we start, here's the format of `printf()` that might be useful for the following "experiments":

| *specifier*  | Output                                                       | Example        |
| ------------ | ------------------------------------------------------------ | -------------- |
| `d` *or* `i` | Signed decimal integer                                       | `392`          |
| `u`          | Unsigned decimal integer                                     | `7235`         |
| `o`          | Unsigned octal                                               | `610`          |
| `x`          | Unsigned hexadecimal integer                                 | `7fa`          |
| `X`          | Unsigned hexadecimal integer (uppercase)                     | `7FA`          |
| `f`          | Decimal floating point, lowercase                            | `392.65`       |
| `F`          | Decimal floating point, uppercase                            | `392.65`       |
| `e`          | Scientific notation (mantissa/exponent), lowercase           | `3.9265e+2`    |
| `E`          | Scientific notation (mantissa/exponent), uppercase           | `3.9265E+2`    |
| `g`          | Use the shortest representation: `%e` or `%f`                | `392.65`       |
| `G`          | Use the shortest representation: `%E` or `%F`                | `392.65`       |
| `a`          | Hexadecimal floating point, lowercase                        | `-0xc.90fep-2` |
| `A`          | Hexadecimal floating point, uppercase                        | `-0XC.90FEP-2` |
| `c`          | Character                                                    | `a`            |
| `s`          | String of characters                                         | `sample`       |
| `p`          | Pointer address                                              | `b8000000`     |
| `n`          | Nothing printed.  The corresponding argument must be a pointer to a `signed int`.  The number of characters written so far is stored in the pointed location. |                |
| `%`          | A `%` followed by another `%` character will write a single `%` to the stream. | `%`            |

source: http://www.cplusplus.com/reference/cstdio/printf/

#### question 1: type char

The type *char* can be signed or un signed.

Here's a programme which allows us to know whether for a particular environment, the char is signed or not :

```C
void q1()
{
        char c=0xFF;
        printf("%c\n",c);
        if(c==-1) printf("signed\n");
        else printf("unsigned\n");
}

```

It turns out that in the case of my PC, the char is signed.

```Bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
�
signed

```

#### question 2: int, signed int and unsigned int

*int* is equivalent to *signed int* .

The size of these types will depend the development environment. For example, int can be any size >= 16bits.

```C
void q2()
{
        int i;
        signed int si;
        unsigned int usi;
        printf("size of a int:                  %ld bytes\n",sizeof(i));
        printf("size of a signed int:           %ld bytes\n",sizeof(si));
        printf("size of a unsigned int:         %ld bytes\n",sizeof(usi));
        //the return type of sizeof() function is long unsigned int!
        printf("the max value of a (signed)int: %d\n",INT_MAX);
        printf("the min value of a (signed)int: %d\n",INT_MIN);
        printf("the max value of a unsigned int:%u\n",UINT_MAX);
        printf("the min value of a unsigned int:%u\n",UINT_MAX+1);
}
```

Notice that the return type of `sizeof()` is actually long unsigned int, we should use a `%ld` instead of `%d` for `printf()`, otherwise there'd be a compiler error.

Here's the result for my PC:

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
size of a int:			4 bytes
size of a signed int:	4 bytes
size of a unsigned int:	4 bytes
```

Theoretically, if a integral type have n bytes, their max & min value will be:

|      | *signed int* | *unsigned int* |
| ---- | ------------ | -------------- |
| max  | 2^(8n-1)-1   | 2^8n-1         |
| min  | -2^(8n-1)    | 0              |

The `limits.h` header file defines constants with the limits of fundamental integral types for the specific system.

```bash
the max value of a (signed) int:	2147483647
the min value of a (signed) int:	-2147483648
the max value of a unsigned int: 	4294967295
the min value of a unsigned int: 	0
```

#### question 3:  _t data type

While the size of *int* can be different from one computer to another, the size of _t data type (width-specific integral types) is guaranteed:

- int8_t uint8_t : coded on one byte,  representing the signed and unsigned values
- int16_t uint16_t : coded on two bytes,  representing the signed and unsigned values
- ... and so on. ( 32 64 )

But the _t data type are **typedef types** in the `stdint.h` header.

```C
#include <stdint.h>
void q3()
{
        uint8_t super,bof,naze,superman,sousleau;
        super=0x11;
        bof=0b1010;
        naze=8;
        superman=0b10110;
        sousleau=0x2;
        printf("super:          %d\n",super);
        printf("bof:            %d\n",bof);
        printf("naze:           %d\n",naze);
        printf("superman:       %d\n",superman);
        printf("sousleau:       %d\n",sousleau);

}
```

> Different ways of integer declaration:
>
> - décimal 42
>
> - hexadécimal 0x2A
>
> - binaire 0b101010. 
>
>   Cette manière de noter est valide chez GCC mais appartient à une extension GCC râle si l’option-pedantic est indiquée.

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
super:		17
bof:		10
naze:		8
superman:	22
sousleau:	2
```

#### question 4: *long* and *long long*

```C
void q4()
{
        long l;
        long long ll;
        printf("size of a long:                 %ld bytes\n",sizeof(l));
        printf("size of a long long:            %ld bytes\n",sizeof(ll));
}
```

```C
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
size of a long:			8 bytes
size of a long long:		8 bytes
```

> Le standard C99 indique qu’un long doit être au moins sur 4 octets, et qu’un long doit être au moins sur 8. Rien de plus n’est spécifié.

#### question 5: overflow of  *unsigned char*  and *signed char*

Be careful with overflow of capacity

```c
void q5()
{
        signed char sc=SCHAR_MAX+1;
        unsigned char uc=UCHAR_MAX+1;
        printf("the max+1 of a signed char:     %d\n",sc);
        printf("the max+1 of a unsigned char:   %d\n",uc);
}
```

The integral types are coded by 2's complement:

```bash
Part1.c: In function ‘q5’:
Part1.c:53:19: warning: large integer implicitly truncated to unsigned type [-Woverflow]
  unsigned char uc=UCHAR_MAX+1;
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
the max+1 of a signed char:	-128
the max+1 of a unsigned char:	0
```

#### question 6: overflow of  *int*

```c
void q6()
{
        int i=INT_MAX+1;
        printf("the max+1 of a int:     %d\n",i);
}
```

```bash
Part1.c:59:15: warning: integer overflow in expression [-Woverflow]
  int i=INT_MAX+1;
               ^
gcc -o Part1 Part1.o -lm
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
the max+1 of a int:	-2147483648
```

#### question 7: undefined behavior

The overflow of a signed int is a [undefined beharvior](https://en.wikipedia.org/wiki/Undefined_behavior#Examples_in_C_and_C++), while the overflow of a unsigned int is a well-defined behavior.

| Expression | Result           |
| ---------- | ---------------- |
| UINT_MAX+1 | 0                |
| LONG_MAX+1 | undefined        |
| INT_MAX+1  | undefined        |
| 1<<-1      | undefined        |
| 1<<0       | 1                |
| 1<<31      | undefined in C99 |
| 1<<32      | undefined        |
| 1/0        | undefined        |

```c
void q7()
{
        uint32_t a,b= 4000000000,c= 500000000,d=0;
        a=(b+c)-d;
        printf("a:%d\n",a);
}
```

205032704=4000000000+500000000-2^32

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
a:205032704
```

#### question 8: comparison bewteen signed ant unsigned int

```C
void q8()
{
        if (sizeof(int) < -1)
        printf("Bizarre, bizarre ... ??\n");
        else
        printf ("Tout semble normal\n");
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
Bizarre, bizarre ... ??
```

This is becourse that the return type of `sizeof()` is long unsigend int, so -1 is automatically casted to a huge positive number.

#### question 9: floating type

```C
void q9()
{
        int i=3.14;
        float f=3.14;
        double d=3.14;
        float lf=3.14159265358979328462264338327;
        double ld=3.14159265358979328462264338327;
        printf("3.14    int:    %d\n",i);
        printf("3.14    float:  %f\n",f);
        printf("3.14    double: %f\n",d);
        printf("long    float:  %f\n",lf);
        printf("long    double: %f\n",ld);
}
```

By default, `printf(""%f")` will display 7 digits:

```BASH
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
3.14	int:	3
3.14	float:	3.140000
3.14	double:	3.140000
long 	float:	3.141593
long 	double:	3.141593
```

#### question 10: floating type II

**noramalization** of a floating type:
$$
\begin{align*}
1.101001\times2^ {12}
(\ sign:positive\ exponent:12\ mantissa:101001)
\end{align*}
$$
In the IEEE formats:

| Type           | Sign | Exponent | Mantissa |
| -------------- | ---- | -------- | -------- |
| Single(float)  | 1    | 8        | 23       |
| Double(double) | 1    | 11       | 52       |

- The IEEE doesn't use 2's complement to code the exponent, so if we convert a dicimal number to a IEEE float type, we should add  a bias127 for the exponent !

  So in the case of a single precision floating, the actual exponent varies between -127 and 128 ! ( 0-127 and 255-127)

- The MSB of matissa represents 2^-1 and so on...

The formula for the conversion from a IEEE float type to a decimal number is :
$$
\begin{align*}
-1^s\times(1+m)\times2^{e}
\end{align*}
$$

| Type           | Exponent bias | Bits precision (1. is implicit) | Number of decimal digits |
| -------------- | ------------- | ------------------------------- | ------------------------ |
| Single(float)  | 127           | 24                              | ~7.2                     |
| Double(double) | 1023          | 53                              | ~15.9                    |

$$
\begin{align*}
2^{24}=16777216\ \ \ \ \ \ 2^{53}=9.00719925474\times10^{15}
\end{align*}
$$

```c
void q10()
{
        int i=3.14;
        float f=3.14;
        double d=3.14;
        float lf=3.14159265358979328462264338327;
        double ld=3.14159265358979328462264338327;
        printf("3.14    int:    %d\n",i);
        printf("3.14    float:  %.29f\n",f);
        printf("3.14    double: %.29f\n",d);
        printf("long    float:  %.29f\n",lf);
        printf("long    double: %.29f\n",ld);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
3.14	int:	3
3.14	float:	3.14000010490417480468750000000
3.14	double:	3.14000000000000012434497875802
long 	float:	3.14159274101257324218750000000
long 	double:	3.14159265358979311599796346854
```

Notice that for float, the meaningful number of decimal digits is always 7 (including 3.) and for double, the meaningful number of decimal digits is always 15 (including 3.).

#### question 11: type bool

```C
#include <stdbool.h>
void q11()
{
        printf("size of a bool: %ld byte\n",sizeof(bool));
        printf("value of true:  %d\n",true);
        printf("value of false: %d\n",false);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
size of a bool:	1 byte
value of true:	1
value of false:	0
```

#### question 12: addition of char and int

```C
void q12()
{
        char mychar = 'A';
        int val = mychar + 10;//mychar converted to int before the addition
        printf("val = %d char = %c\n", val,val);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
val = 75 char = K
```

#### question 13: "false "subtraction de unsigned int

```C
void q13()
{
        uint16_t a = 413;
        uint16_t b = 64948;
        fprintf(stdout, "%u\n", (a - b));
}
```

```BASH
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
4294902761
```

The type of the result is clearly not *uint16_t*, since the max value of a *uint16_t* is 65535. (seems a implicit conversion from *uint16_t* to *uint32_t* took place).

#### question 14: "right" subtraction de unsigned int

> Conversion implicite de type
>
> Si un opérateur a des opérandes de différents types, les valeurs des opérandes sont converties
>
> automatiquement dans un type commun. Lors d’une affectation, la donnée à droite du signe d’égalité
>
> est convertie dans le type à gauche du signe d’égalité. Dans ce cas, il peut y avoir perte de précision
>
> si le type de la destination est plus faible que celui de la source. De même, lors de l’appel d’une
>
> fonction, les paramètres sont automatiquement convertis dans les types déclarés dans la définition
>
> de la fonction.
>
> Dans n’importe quelle expression entière, si un int peut représenter toutes les valeurs de cette
>
> expression (par exemple uint16_t ), alors il est converti implicitement par le compilateur en
>
> int. Si cela ne suffit pas, la conversion est faite vers unsigned int , si possible.
>
> Dans le cas où une opération artithmétique est efectuée entre deux expressions qui n’ont pas le
>
> même type après la conversion entière décrite plus haut, alors la conversion de type continue selon
>
> les règles suivantes :
>
> — si les deux opérandes sont de type flottant, alors l’opérande ayant le rang le plus bas est
>
> converti vers un type de même rang que l’autre opérande, l’ordre des rangs étant définie
>
> comme suit : float -> double -> long double.
>
> — si un seul des opérande est est de type flottant, le type entier est converti dans ce type flottant.
>
> — si les deux opérandes sont de type entier, alors :
>
> ​	— si les deux opérandes sont tous deux de de type non-signé, ou tous deux de type signé,
>
> ​	le type de plus petit rang est converti dans l’autre, la hiérarchie de rang chez les entiers
>
> ​	étant la suivante :
>
> ​	\1.  long long int, unsigned long long int
>
> ​	\2.  long int, unsigned long int
>
> ​	\3.  int, unsigned int
>
> ​	\4.  short int, unsigned short int
>
> ​	\5.  signed char, char, unsigned char
>
> — sinon si le type Tu d’un des opérande est non signé et a un rang égal ou supérieur au
>
> type T de l’autre opérande, alors T est convertie dans Tu.
>
> — sinon, si le type Ts de l’un des opérande est signé et peut représenter toutes les valeurs
>
> de l’autre opérande, alors T est converti en Ts
>
> — sinon les deux opérandes sont converties dans le type entier non signé correspondant
>
> au type de l’opérande qui a un type signé.
>
> Si une perte de précision est possible lors de la conversion implicite de type, le compilateur peut
>
> génèrer un warning.
>
> Exemples :
>
> int 		2 + 3 		int 2 + int 3→int 5
>
> double 	2.2 + 3.3 	double 2.2 + double 3.3 →double 5.5
>
> mix 	2 + 3.3		 int 2 + double 3.3→double 2.0 + double 3.3→double 5.3
>
> int		1 / 2		int 1 / int 2→int 0
>
> double	1.0 / 2.0		double 1.0 / double 2.0→double 0.5
>
> mix		1 / 2.0		int 1 / double 2.0→double 1.0 / double 2.0→double 0.5

```c
void q14()
{
        uint16_t a = 413;
        uint16_t b = 64948;
        uint16_t c=a-b;
        fprintf(stdout, "%u\n", c);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
1001
```

#### question 15: non correct conversion(mantissa trick!)

```c
void q15()
{
        long a = 8000000002;
        float b = 2;
        long c = a / b;
        printf("res : %li\n", c);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
res : 4000000000
```

- fisrt implicit conversion:

   `a/b` gives us actually a float, since the number of decimal digits is about 7, a float type is unable to represent correctly 4000000001 ( it's something like 4000000000.000).

- second implicit conversion:

  `long c=a/b` conversion from float to long int.

#### question 16: addition of a *float* and a *long*

If we try to add a float and a long, the implicit conversion from long to float will take place.

```c
void q16()
{
        long l=142857142857;
        float f=0;
        printf("l+f : %f\n",l+f);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
l+f : 142857142272.000000
```

#### question 17: assignment of a int

If we try to assign a floating value to a int, the "float" will be truncated.

```c
void q17()
{
        int i=1.618;
        printf("i : %d\n",i);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
i : 1
```

### Explicit cast

#### question 19: between int and char

```c
void q19()
{
        char c=42;
        int i=(char)c;
        printf("i: %d\n",i);
        i=42;
        c=(char)i;
        printf("c: %c\n",c);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
i: 42
c: *
```

#### question 20:

```C
void q20()
{
        int i=-42;
        unsigned int u=(unsigned int)i;
        printf("unsigend int: %u\n",u);
        int ii=0x2a3b;
        char c=(char)ii;
        printf("char : %c\n",c);
}
```

```BASH
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
unsigend int: 4294967254
char : ;
```

By reading the ASCII table, ';' corresponds to the hex number 3b. (which takes 1 byte)

#### question 21: 

```c
void q21()
{
        char A=3;
        int B=4;
        float C=A/B;
        printf("C: %f\n",C);
        C=(float)A/(float)B;
        printf("C: %f\n",C);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
C: 0.000000
C: 0.750000
```

### Bits-to-bits operations

| operation      | operator  | example               |
| -------------- | --------- | --------------------- |
| shift          | \>> or << | a=b<<5                |
| xor            | ^         |                       |
| 1's complement | ~         | ~0b0101 = 0b1010      |
| and            | &         | 0b0111&0b1101=0b0101  |
| or             | \|        | 0b0001\|0b0001=0b1001 |

**&&,|| and == are the logical operators**

#### question 22

```C
void printRoomsState(uint32_t allRooms)
{
        int index=0;
        while(index<32){
                printf("%d: %d  ",index++,allRooms%2);
                allRooms%2?
                        printf("Occupé\n"):printf("Non occupé\n");
                allRooms=allRooms>>1;
        }
}
int main()
{
        printRoomsState(5);
        return 0;
}
```

```BASH
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
0: 1	Occupé
1: 0	Non occupé
2: 1	Occupé
3: 0	Non occupé
4: 0	Non occupé
5: 0	Non occupé
6: 0	Non occupé
7: 0	Non occupé
8: 0	Non occupé
9: 0	Non occupé
10: 0	Non occupé
11: 0	Non occupé
12: 0	Non occupé
13: 0	Non occupé
14: 0	Non occupé
15: 0	Non occupé
16: 0	Non occupé
17: 0	Non occupé
18: 0	Non occupé
19: 0	Non occupé
20: 0	Non occupé
21: 0	Non occupé
22: 0	Non occupé
23: 0	Non occupé
24: 0	Non occupé
25: 0	Non occupé
26: 0	Non occupé
27: 0	Non occupé
28: 0	Non occupé
29: 0	Non occupé
30: 0	Non occupé
31: 0	Non occupé
```

#### question 23:

```C
uint32_t roomGoesOccupied(uint32_t allRooms,unsigned int roomNb)
{
        uint32_t operand=1<<roomNb;
        return operand|allRooms;
}
int main()
{
        printRoomsState(roomGoesOccupied(5,24));
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
0: 1	Occupé
1: 0	Non occupé
2: 1	Occupé
3: 0	Non occupé
4: 0	Non occupé
5: 0	Non occupé
6: 0	Non occupé
7: 0	Non occupé
8: 0	Non occupé
9: 0	Non occupé
10: 0	Non occupé
11: 0	Non occupé
12: 0	Non occupé
13: 0	Non occupé
14: 0	Non occupé
15: 0	Non occupé
16: 0	Non occupé
17: 0	Non occupé
18: 0	Non occupé
19: 0	Non occupé
20: 0	Non occupé
21: 0	Non occupé
22: 0	Non occupé
23: 0	Non occupé
24: 1	Occupé
25: 0	Non occupé
26: 0	Non occupé
27: 0	Non occupé
28: 0	Non occupé
29: 0	Non occupé
30: 0	Non occupé
31: 0	Non occupé
```

#### question 24: 

```c
bool isOccupied(uint32_t allRooms,unsigned int roomNb)
{
        return (allRooms>>roomNb)%2;
}
int main()
{
        printf("%d\n",isOccupied(5,2));
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
1
```

#### question 25:

```c
uint32_t roomGoesEmpty(uint32_t allRooms,unsigned int roomNb)
{
        uint32_t operand=1<<roomNb;
        return (~operand)&allRooms;
}
int main()
{
        printRoomsState(roomGoesEmpty(5,0));
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
0: 0	Non occupé
1: 0	Non occupé
2: 1	Occupé
3: 0	Non occupé
4: 0	Non occupé
5: 0	Non occupé
6: 0	Non occupé
7: 0	Non occupé
8: 0	Non occupé
9: 0	Non occupé
10: 0	Non occupé
11: 0	Non occupé
12: 0	Non occupé
13: 0	Non occupé
14: 0	Non occupé
15: 0	Non occupé
16: 0	Non occupé
17: 0	Non occupé
18: 0	Non occupé
19: 0	Non occupé
20: 0	Non occupé
21: 0	Non occupé
22: 0	Non occupé
23: 0	Non occupé
24: 0	Non occupé
25: 0	Non occupé
26: 0	Non occupé
27: 0	Non occupé
28: 0	Non occupé
29: 0	Non occupé
30: 0	Non occupé
31: 0	Non occupé
```

### Create a type

### Enumeration

If we want to typedef a enum:

```c
enum scrutin_e {MAJORITAIRE_UNI, MAJORITAIRE_PLURI, PROPORTIONNEL, MIXTE};
typedef enum scrutin_e scrutin_t;
```

#### question 29: Different ways to declare a enum

```c
void q29()
{
        enum scrutin_e1 {MAJORITAIRE_UNI1,MAJORITAIRE_PLURI1,PROPORTIONNEL1,MIXTE1};
        printf("scrutin_e1: %d %d %d %d\n",MAJORITAIRE_UNI1,MAJORITAIRE_PLURI1,PROPORTIONNEL1,MIXTE1);
        enum scrutin_e2 {MAJORITAIRE_UNI2=2,MAJORITAIRE_PLURI2=8,PROPORTIONNEL2=42,MIXTE2=12};
        printf("scrutin_e2: %d %d %d %d\n",MAJORITAIRE_UNI2,MAJORITAIRE_PLURI2,PROPORTIONNEL2,MIXTE2);
        enum scrutin_e3 {MAJORITAIRE_UNI3=4,MAJORITAIRE_PLURI3,PROPORTIONNEL3,MIXTE3};
        printf("scrutin_e3: %d %d %d %d\n",MAJORITAIRE_UNI3,MAJORITAIRE_PLURI3,PROPORTIONNEL3,MIXTE3);
}
```

- Notice that the STRINGs of enums can't be the same even if they are defined in different enums.
- We don't need to declare a enum variable to use its value.

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
scrutin_e1: 0 1 2 3
scrutin_e2: 2 8 42 12
scrutin_e3: 4 5 6 7
```

#### question 30:

```c
void q30()
{
        enum semaine {LUNDI=1,MARDI,MERDREDI,JEUDI,VENDREDI,SAMEDI,DIMANCHE};
}
```

### Switch-case

#### question 31:

```c
void appreciate(int note)
{
        switch (note) {
                case 12:
                        printf("12 ! Passable ");
                        break;
                case 18:
                        printf("18 ! Super ! ");
                case 6:
                        printf("6 ! Naze ");
                        break;
                case 8:
                        printf("8 ! Mieux que naze ");
                        break;
                case 10:
                        printf("10 ! Presque passable ");
                        break;
                default:
                        printf("%d ! Pas prevu par le de-qui-corrige", note);
                        break;
        }
        printf("\n");
}
int main()
{
        appreciate(6);
        appreciate(12);
        appreciate(18);
        appreciate(14);
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
6 ! Naze 
12 ! Passable 
18 ! Super ! 6 ! Naze 
14 ! Pas prevu par le de-qui-corrige
```

- Since there's no `break` for the case of 18, the following cases are also excuted till we meet a `break`
- But the `break` of the default case is not necessary.

#### question 32:

```c
void q32(int n)
{
        if(!n){
                printf("Ga\n");
        }
        while(n>0){
                switch(n%4){
                        case 0:
                                printf("Ga ");
                                break;
                        case 1:
                                printf("Bu ");
                                break;
                        case 2:
                                printf("Zo ");
                                break;
                        case 3:
                                printf("Meu ");
                }
                n/=4;
        }
        printf("\n");
}
int main()
{
        q32(3);
        q32(6);
        q32(11);
        q32(42);
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part1 
Meu 
Zo Bu 
Meu Zo 
Zo Zo Zo 
```

## Part 2

pointer, array, static allocation, parametered main function

### Dereference & acces to an address

#### question 1: address of *main()*

```c
int main();
void q1(){
        printf("%p\n",&main);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
0x565247308e65
```

![Screenshot_2019-01-02 TP-etu pdf](/home/mengxin/Downloads/Screenshot_2019-01-02 TP-etu pdf.png)

The `main()` belongs to the **Text segment**(read only)

#### question 2 3 4: address of the global variables

```c
int intNotInitialized;
int intInitialized=0;
void q2(){
        intNotInitialized=42;
        intInitialized=5;
        int* addresseNot=&intNotInitialized;
        int* addresseInit=&intInitialized;
        printf("la valeur de intNotInitialized: %d\n",intNotInitialized);
        printf("l'addresse de intNotInitialized:%p\n",addresseNot);
        printf("la valeur de intInitialized:    %d\n",intInitialized);
        printf("l'addresse de intInitialized:   %p\n",addresseInit);
        *addresseNot=43;
        *addresseInit=6;
        printf("après la modification:\n");
        printf("la valeur de intNotInitialized: %d\n",intNotInitialized);
        printf("la valeur de intInitialized:    %d\n",intInitialized);
}
```

The global variables are located in the **BSS segment**

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
la valeur de intNotInitialized:	42
l'addresse de intNotInitialized:0x55daf5c0c018
la valeur de intInitialized:	5
l'addresse de intInitialized:	0x55daf5c0c014
après la modification:
la valeur de intNotInitialized:	43
la valeur de intInitialized:	6
```

#### question 5: address of the local variables

```c
void q5(){
        int localeNot;
        int localeInit=0;
        printf("la valeur de localeNot:         %d\n",localeNot); 
        printf("l'addresse de localeNot:        %p\n",&localeNot);
        printf("la valeur de localeInit:        %d\n",localeInit);
        printf("l'addresse de localeInit:       %p\n",&localeInit);
}
```

The local variables are located in the **stack**.

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
la valeur de localeNot:		-754673785
l'addresse de localeNot:	0x7ffc36a7ab70
la valeur de localeInit:	0
l'addresse de localeInit:	0x7ffc36a7ab74
```

The value of a non initialized local variable is actually the value which already exists before the program excute, while a non initialized globle int is 0. 

### Array

#### question 6: `sizeof()`

```c
void q6(int size){
        int all_elements[size];
        printf("%ld\n",sizeof(all_elements));
}
int main(int argc,char * argv[]){
        int number_of_elements=atoi(argv[1]);
        q6(number_of_elements);
        return 0;
}
```

`sizeof()` is a operator just like + - * are.

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2  10
40
```

`sizeof()` applied on a array, returns the number of bytes occupied by this array.<

#### question 7: define a new array type

- define MAX_SIZE with unsigned int:

  ```c
  unsigned int MAX_SIZE=5;
  typedef int matrix [MAX_SIZE][MAX_SIZE];causes a compiler error:
  ```

  causes  a compiler error

  ```
  Part2.c:11:13: error: variably modified ‘matrix’ at file scope
   typedef int matrix [MAX_SIZE][MAX_SIZE];
  ```

- define MAX_SIZE with const unsigned int:

  ```c
  const unsigned int MAX_SIZE=5;
  typedef int matrix [MAX_SIZE][MAX_SIZE];
  ```

  also causes a compiler error:

  ```bash
  Part2.c:11:13: error: variably modified ‘matrix’ at file scope
   typedef int matrix [MAX_SIZE][MAX_SIZE];
  ```

- define MAX_SIZE with a maro:

  ```c
  #define MAX_SIZE 5
  typedef int matrix [MAX_SIZE][MAX_SIZE];
  //order of [][] and "matrix"!
  ```

  this kind of definition works

#### question 8: 

```c
void q8(int (*a)[5],int size){
        //int (*a)[5]:  a pointer which points an array containing 5 int
        //int *a [5]:   a array which contains 5 pointer of int
        for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                        printf("%d      ",a[i][j]);
                }
                printf("\n");
        }
}
int main(int argc,char * argv[]){
        matrix mymatrix;
        q8(mymatrix,MAX_SIZE);
        return 0;
}
```

It's imfortant ot distinguish the differents meaning of declarations of a complex array type:

- `int (*a)[5]`:  a pointer which points an array containing 5 int
- `int *a [5]`:   a array which contains 5 pointer of int

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
0	0	1935634848	32764	-1	
0	0	0	1935663720	32764	
-998836464	32594	0	0	0	
0	0	0	1970169159	0	
9	0	-1001093536	32594	1935635000	
```

It's normal that some values of the mymatrix seem to be random: mymatrix is a non initialized local variable.

### String

#### question 9 10: traversing a string with while

```c
void q9(){
        char * my_string="<-_->";
        printf("%s\n",my_string);
        char * pt=my_string; 
        while(*pt!='\0'){
                printf("%c.",*pt);
                pt++;
        }
        printf("\n");
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
<-_->
<.-._.-.>.
```

#### question 11: traversing a string with for

```c
void q11(){
        char* my_string="<-_->";
        for(int i=0;i<strlen(my_string);i++){
                printf("%c.",my_string[i]);     
        }
        printf("\n");
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
<.-._.-.>.
```

#### question 12: conversion from string to int

```
void q12(){
        char myString[50];
        scanf("%s",myString);
        int i=strtoimax(myString,NULL,10);
        printf("%d\n",i%4);
}
```

#### question 13: diy strcmp()

```c
int TP_strcmp(const char* s1,const char* s2)
{
        int ret=0;
        int i=0;
        while(s1[i]!='\0'&&s2[i]!='\0'){
                if(s1[i]!=s2[i]){
                        ret=s1[i]-s2[i];
                        break;
                }
                i++;
        }
        if(!ret){
                if(s1[i]!='\0') ret=1;
                if(s2[i]!='\0') ret=-1;
        }
        return ret;
}
int main(int argc,char * argv[]){
        printf("%d\n",TP_strcmp("hello","hello"));
        printf("%d\n",TP_strcmp("hello world","hello"));
        printf("%d\n",TP_strcmp("chris evans","chris pratt"));
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
0
1
-11
```

### Pointer/array equivalence

#### question 14 15:

```c
void q14(){
        int tab[5][7];
        int* tab_addr=&tab;
        int* tab_point=tab;
        int* tab_point_elt=&tab[0];
        printf("tab_addr:       %p\n",tab_addr);
        printf("tab_point:      %p\n",tab_point);
        printf("tab_point_elt:  %p\n",tab_point_elt);
        printf("tab[2][2]               %d\n",tab[2][2]);
        printf("tab[1][5]               %d\n",tab[1][5]);
        printf("*tab_point_elt+12       %d\n",*(tab_point_elt+12));
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
tab_addr:	0x7fffb5bc0e40
tab_point:	0x7fffb5bc0e40
tab_point_elt:	0x7fffb5bc0e40
tab[2][2]		0
tab[1][5]		-1245744536
*tab_point_elt+12	-1245744536
```

- `&tab`, `tab`, `&tab[0]` mean the same address
- `int tab[5][7]`is a array which contains 5 array containing 7 int

### Structures

#### question 16: birthday type

```c
enum mois {Jan,Feb,Mar,Avr,Mai,Jun,Jui,Aou,Sep,Oct,Nov,Dec};
typedef struct{
        int year;
        enum mois month;
        int day;
}birthday;
```

#### question 17: student type

```c
typedef struct{
        int id;
        birthday b;
        char boissonPreferee[20];
        char nom[20];
}student;
```

#### question 18: declaration of structures

```c
int main(int argc,char * argv[]){
        student fetard [3];
        printf("%d\n",fetard[0].b.month);
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
827681440
```

### pointer arithmetics

#### question 20:

```c
void q20(){
        int A[]={12,23,34,45,56,67,78,89,90};
        int *P;
        P=A;
        int i1=*P+2;            //14
        int i2=*(P+2);          //34
        int* a1= &A[4]-3;       //A[1]
        int* a2=A+3;            //A[3]
        int i3=&A[7]-P;         //7
        int* a3=P+(*P-10);      //A[2]
        int i4=*(P+*(P+8)-A[7]);//23
        int i=0;
        for(i=0;i<9;i++){
                printf("A[%d]:%p\n",i,&A[i]);
        }
        printf("i1:%d\n",i1);
        printf("i2:%d\n",i2);
        printf("a1:%p\n",a1);
        printf("a2:%p\n",a2);
        printf("i3:%d\n",i3);
        printf("a3:%p\n",a3);
        printf("i4:%d\n",i4);
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 
A[0]:0x7ffd882fb400
A[1]:0x7ffd882fb404
A[2]:0x7ffd882fb408
A[3]:0x7ffd882fb40c
A[4]:0x7ffd882fb410
A[5]:0x7ffd882fb414
A[6]:0x7ffd882fb418
A[7]:0x7ffd882fb41c
A[8]:0x7ffd882fb420
i1:14
i2:34
a1:0x7ffd882fb404
a2:0x7ffd882fb40c
i3:7
a3:0x7ffd882fb408
i4:23
```

#### question 21: gdb

We can also use a gdb to supervisor the value of variables.

![Screenshot_2019-01-02 TP-etu pdf(1)](/home/mengxin/Downloads/Screenshot_2019-01-02 TP-etu pdf(1).png)

#### question 22: priority of *  and + / & and +

- \* has a greater priority than +
- & has a greater priority than +

### Parametered main()

`int main(int argc, char* argv[])`: the type of argv is a array which contains the pointer of char (string)

#### question 23: display all parameters

```c
int main(int argc,char * argv[]){
        int i;
        for(i=0;i<argc;i++){
                printf("%s\n",argv[i]);
        }
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2  arg1 arg2 arg3
./Part2
arg1
arg2
arg3
```

#### question 24: argv[0]

argv[0] corresponds to the name of executable

#### question 25:

```c
int main(int argc,char * argv[]){
	if(argv[1]){
                long int li=strtol(argv[1],NULL,10);
                int i;
                for(i=0;i<li;i++){
                        printf("*");
                }
                printf("\n");
        }else{
                printf("no number\n");
        }
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2
no number
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2 5
*****
```

### r-value l-value

> lvalue and rvalue
>
> Un objet est un emplacement mémoire identifiable (par exemple une variable locale int locale).
>
> Contre-exemple : le résultat d’une opération arithmétique n’est pas un objet. Une l-value est une expression identifiant un objet ; elle a donc un emplacement mémoire identifiable. Elle peut donc être affectée. Par exemple : locale = 4. Une l-value peut donc être :
>
> —  le nom d’une variable (de n’importe quel type)
>
> —  un emplacement d’un tableau (via l’opérateur[])
>
> —  un déréférencement (via l’opérateur*)
>
> —  un accès à un membre d’une structure
>
> —  une l-value entre parenthèse
>
> Une r-value est une valeur qui ne persiste pas après son usage dans une expression. Par exemple
>
> la valeur 4. Elle n’a pas d’emplacement mémoire identifiable.
>
> Une l-value peut être utilisée comme une r-value mais l’inverse n’est pas vrai !

#### question 26:

- ```c
  void q26()
  {
          int var=0; 4=var;
          (var+1)=4;
  }
  ```

  ```bash
  Part2.c: In function ‘q26’:
  Part2.c:159:14: error: lvalue required as left operand of assignment
    int var=0; 4=var;
                ^
  Part2.c:160:9: error: lvalue required as left operand of assignment
    (var+1)=4;
  ```

- ```c
  void q26()
  {
          int arr[]={1,2};
          int* p=&arr[0];
          *(p+1)=10;
  }
  ```

  No error.

- ```c
  void q26()
  {
          int var=10;
          int* addr=&(var+1);
  }
  ```

  ```bash
  Part2.c: In function ‘q26’:
  Part2.c:165:12: error: lvalue required as unary ‘&’ operand
    int* addr=&(var+1);
  ```

- ```c
  void q26()
  {
          typedef enum color{red,green,blue} color;
          color c;
          c=green;
          blue=green;
  }
  ```

  ```bash
  Part2.c: In function ‘q26’:
  Part2.c:169:6: error: lvalue required as left operand of assignment
    blue=green;
        ^
  ```

- ```c
  void q26()
  {
          int var=0;
          &var=40;
  }
  ```

  ```bash
  Part2.c: In function ‘q26’:
  Part2.c:171:6: error: lvalue required as left operand of assignment
    &var=40;
        ^
  ```

### Function pointer

Two ways to use a function pointer:

1.  As a variable:

   We should specify the parameters and the return type to declare a function pointer.

   We can assign to a funtion pointer an address of a function

   ```c
   int max(int x,int y)
   {
       return x>y? x:y;
   }
   int(*p)(int,int);
   p=&max;//& can be omitted
   int a=1,b=2
   int bigger=p(a,b)// same thing as int bigger=max(a,b)
   ```

2. As a parameter:

   These two signatures work both.

   ```c
   void foo(int pfunc(int),int* tab,int size);
   void foo(int (* pfunc)(int),int *tab,int size);
   ```

#### question 27 28 29:

```c
int fois_deux(int a)
{
        return 2*a;
}
void appliquer_tableau(int pfunc(int),int* tab,int size)
{
        int i;
        for(i=0;i<size;i++){
                tab[i]=pfunc(tab[i]);
        }
}
int main(int argc,char * argv[]){
        int arr[]={1,2,3,4,5};
        appliquer_tableau(&fois_deux,arr,5);
        int i;
        for(i=0;i<5;i++){
                printf("%d ",arr[i]);
        }
        printf("\n");
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2
2 4 6 8 10 
```

#### question 30:

```c
int superieur(int a,int b){
        if(a>b) return 1;
        else if(a<b) return -1;
        else return 0;
}
int inferieur(int a,int b){
        if(a<b) return 1;
        else if(a>b) return -1;
        else return 0;
}
void tri(int* t, int n,int(* compare)(int,int))
{
        int i, i_max, j, tmp;
        for(i=0 ; i < n-1 ; i++) {
                i_max=i;
                for(j=i; j<n; j++) {
                        if(compare(t[j],t[i_max])==1) {
                                i_max=j;
                        }
                }
        tmp = t[i_max];
        t[i_max] = t[i];
        t[i] = tmp;
        }
}
int main(int argc,char * argv[]){
        int arr[]={3,8,7,5,4};
        tri(arr,5,inferieur);
        int i;
        for(i=0;i<5;i++){
                printf("%d ",arr[i]);
        }
        printf("\n");
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part2
3 4 5 7 8 
```

## Part 3

Input, output

### Language de bois

#### question 1: `fgets()`

```c
char *fgets(char *s, int size, FILE *stream);
```

> ```
>    fgets()  reads in at most one less than size characters from stream and
>    stores them into the buffer pointed to by s.  Reading  stops  after  an
>    EOF  or a newline.  If a newline is read, it is stored into the buffer.
>    A terminating null byte ('\0') is stored after the  last  character  in
>    the buffer.
> ```
>
>

Threes cases that ends the lecture of `fgets()`:

1. number of characters reaches the end
2. an EOF
3. a newline

#### question 2: lecture of a file

```c
int getc(FILE *stream);
```

>        fgetc()  reads  the  next  character  from  stream and returns it as an
>        unsigned char cast to an int, or EOF on end of file or error.

```c
FILE *fopen(const char *pathname, const char *mode);
```

> ```
> The fopen() function opens the file whose name is the string pointed to by pathname and associates a stream with it.
> 
>    The argument mode points to a string beginning with one of the  follow‐
>    ing sequences (possibly followed by additional characters, as described
>    below):
> 
>    r      Open text file for reading.  The stream  is  positioned  at  the
>           beginning of the file.
> 
>    r+     Open  for  reading and writing.  The stream is positioned at the           		 beginning of the file.
> 
>    w      Truncate file to zero length or create text  file  for  writing.
>           The stream is positioned at the beginning of the file.
> 
>    w+     Open  for  reading  and writing.  The file is created if it does
>           not exist, otherwise it is truncated.  The stream is  positioned
>           at the beginning of the file.
>    a      Open  for  appending (writing at end of file).  The file is cre‐
>           ated if it does not exist.  The stream is positioned at the  end
>           of the file.
> 
>    a+     Open  for  reading  and appending (writing at end of file).  The
>           file is created if it does not exist.  The initial file position
>           for  reading  is  at  the  beginning  of the file, but output is
>           always appended to the end of the file.
> ```
>
>

```c
void q2(){
        FILE *stream=fopen("file.txt","r");
        char c;
        c=getc(stream);
        while(c!=EOF){
                printf("%c",c);
                c=getc(stream);
        }
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part3
This is a demo file.
Here we go.
End.
```

#### question 3:

```C
void q3(FILE* newfile){
        int i;
        for(i=1;i<=4;i++){
                char name[80]="colonne";
                char index[2];
                index[0]=i+'0';//trick
                index[1]='\0';//indispensable
                strcat(name,index);
                strcat(name,".txt");
                FILE *colonne=fopen(name,"r");
                int nb=rand()%8;
                int compteur=0;
                char phrase[101];
                while(compteur<=nb){
                        fgets(phrase,100,colonne);
                        compteur++;
                }
                fputs(phrase,newfile);
                fclose(colonne);
        }
}
int main(){
        FILE *bois=fopen("bois.txt","w+");
        q3(bois);
        fclose(bois);
        return 0;
}
```

```
Et ce n'est certainement pas vous, mes chers compatriotes, qui me contredirez si je vous dis que
l'aspiration plus que legitime de chacun au progres social
oblige a la prise en compte encore plus effective
d'une valorisation sans concession de nos caracteres specifiques.
```

#### question 4:

```c
void q4(){
        int i;
        FILE *discours=fopen("discours.txt","w+");
        for(i=0;i<5;i++){
                q3(discours);
        }
        fclose(discours);
}
```

```
Et ce n'est certainement pas vous, mes chers compatriotes, qui me contredirez si je vous dis que
l'aspiration plus que legitime de chacun au progres social
oblige a la prise en compte encore plus effective
d'une valorisation sans concession de nos caracteres specifiques.
Je reste fondamentalement persuade que
la necessite de repondre a votre inquietude journaliere, que vous soyez jeunes ou ages,
interpelle le citoyen que je suis et nous oblige tous a aller de l'avant dans la voie
d'un plan correspondant veritablement aux exigences legitimes de chacun.
Je reste fondamentalement persuade que
le particularisme du a notre histoire unique
interpelle le citoyen que je suis et nous oblige tous a aller de l'avant dans la voie
d'une valorisation sans concession de nos caracteres specifiques.
Des lors, sachez que je me battrai pour faire admettre que
la volonte farouche de sortir notre pays de la crise
a pour consequence obligatoire l'urgente nécessite
d'un programme plus humain, plus fraternel et plus juste.
Je tiens à vous dire ici ma determination sans faille pour clamer haut et fort que
l'acuite des problemes de la vie quotidienne
conforte mon desir incontestable d'aller dans le sens
d'un processus allant vers plus d'egalite.
```

### DIY `printf()`

In this part we can only use `putchar()`to display.

> ```
>    fputc() writes the character c, cast to an unsigned char, to stream.
> 
>    fputs()  writes  the  string  s to stream, without its terminating null
>    byte ('\0').
> 
>    putc() is equivalent to fputc() except that it may be implemented as  a
>    macro which evaluates stream more than once.
> 
>    putchar(c) is equivalent to putc(c, stdout).
> ```

#### question 5: unsigned int

```c
void printf_unsigned_int(unsigned int value){
        char buffer[20];
        int nb=0;
        while(value>0){
                buffer[nb++]=value%10+'0';
                value/=10;
        }
        int i;
        for(i=nb-1;i>=0;i--){
                putchar(buffer[i]);
        }
        if(!nb){
                putchar('0');
        }
}
int main(){
        printf_unsigned_int(0);
        printf("\n");
        printf_unsigned_int(UINT_MAX);
        printf("\n");
        return 0;
}
```

```c
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part3
0
4294967295
```

#### quesiton 6: signed int

```c
void printf_signed_int(int value){
        if(value<0){
                putchar('-');
                printf_unsigned_int(-1*value);
        }else{
                printf_unsigned_int(value);
        }
}
int main(){
        printf_signed_int(INT_MIN);
        printf("\n");
        printf_signed_int(INT_MAX);
        printf("\n");
        return 0;
}
```

```bash
mengxin@mengxin-VirtualBox:~/Documents/Programmation-C$ ./Part3
-2147483648
2147483647
```



## References

http://www.cplusplus.com/reference/cstdio/printf/

http://www.cplusplus.com/reference/climits/7

https://www.cs.utah.edu/~regehr/papers/overflow12.pdf