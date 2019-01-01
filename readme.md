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

#### question 32

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

## References

http://www.cplusplus.com/reference/cstdio/printf/

http://www.cplusplus.com/reference/climits/7

https://www.cs.utah.edu/~regehr/papers/overflow12.pdf