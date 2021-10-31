// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cube struct
typedef struct cube
{
    char ** white;
    char ** yellow;
    char ** blue;
    char ** red;
    char ** orange;
    char ** green;

} Cube;

// Constant arrays that determine rotations
const int rot_edge_col[] = {1, 2, 1, 0, 1};
const int rot_edge_row[] = {0, 1, 2, 1, 0};

const int rot_corner_col[] = {0, 2, 2, 0, 0};
const int rot_corner_row[] = {0, 0, 2, 2, 0};

const int rot_edge_col_inv[] = {1, 0, 1, 2, 1};
const int rot_edge_row_inv[] = {0, 1, 2, 1, 0};

const int rot_corner_col_inv[] = {0, 0, 2, 2, 0};
const int rot_corner_row_inv[] = {0, 2, 2, 0, 0};
 

const int prev_cross[][3][3] = {
    {
        {0, 1, 0},
        {1, 1, 0},
        {0, 0, 0}
    },
    {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 0}
    }  
};

// Function Prototypes
Cube * initials_cube();

void U_move(Cube * cube);
void F_move(Cube * cube);
void R_move(Cube * cube);
void L_move(Cube * cube);
void M_move(Cube * cube);
void D_move(Cube * cube);
void E_move(Cube * cube);

void U_Prime_move(Cube * cube);
void F_Prime_move(Cube * cube);
void R_Prime_move(Cube * cube);
void L_Prime_move(Cube * cube);
void M_Prime_move(Cube * cube);
void D_Prime_move(Cube * cube);
void E_Prime_move(Cube * cube);

int Solved(Cube * cube);
void Orient(Cube * cube);
void W_C(Cube * cube);
void F2L(Cube * cube);
void OLL(Cube * cube);
void PLL(Cube * cube);
void CFOP(Cube * cube);

void color(char a);

void alg_execute(Cube * cube, char * alg);
char * alg_find(char * alg);

void printCube(Cube * cube);


// Main Function
int main()
{
    Cube * cube = initials_cube();

    printCube(cube);
    printf("\n");

    alg_execute(cube,  "RRLLFFFUURUFURUuFUURFUFLRUFFURLULUFLRUFLLLLFURdDUDLUURLDUFRLUDYYUFUFFURlrLUrul");
    printf("Scramble cube:\n\n");

    printCube(cube);

    Orient(cube);

    return 0;
}

// Functions that executes a U move on the cube struct
void U_move(Cube * cube)
{
    // Variables
    int i;
    char temp_edge = cube->yellow[rot_edge_row[0]][rot_edge_col[0]];
    char temp_corner = cube->yellow[rot_corner_row[0]][rot_corner_col[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->yellow[rot_edge_row[i + 1]][rot_edge_col[i + 1]];
        char temp_corner1 = cube->yellow[rot_corner_row[i + 1]][rot_corner_col[i + 1]];
        
        cube->yellow[rot_edge_row[i + 1]][rot_edge_col[i + 1]] = temp_edge;
        cube->yellow[rot_corner_row[i + 1]][rot_corner_col[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->blue[0][2 - i];
        char temp_faces1 = cube->orange[0][2 - i];

        cube->orange[0][2 - i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->green[0][i];

        cube->green[0][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->red[0][i];

        cube->red[0][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->blue[0][2 - i];

        cube->blue[0][2 - i] = temp_faces;
    }

}

// Functions that executes a R move on the cube struct
void R_move(Cube * cube)
{
    // Variables 
    int i;
    char temp_edge = cube->orange[rot_edge_row_inv[0]][rot_edge_col_inv[0]];
    char temp_corner = cube->orange[rot_corner_row_inv[0]][rot_corner_col_inv[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->orange[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]];
        char temp_corner1 = cube->orange[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]];
        
        cube->orange[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]] = temp_edge;
        cube->orange[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->yellow[i][2];
        char temp_faces1 = cube->blue[2 - i][2];

        cube->blue[2 - i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->white[i][2];

        cube->white[i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->green[i][2];

        cube->green[i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->yellow[i][2];

        cube->yellow[i][2] = temp_faces;
    }
}

// Functions that executes a L move on the cube struct
void L_move(Cube * cube)
{
    // Variables
    int i;
    char temp_edge = cube->red[rot_edge_row[0]][rot_edge_col[0]];
    char temp_corner = cube->red[rot_corner_row[0]][rot_corner_col[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->red[rot_edge_row[i + 1]][rot_edge_col[i + 1]];
        char temp_corner1 = cube->red[rot_corner_row[i + 1]][rot_corner_col[i + 1]];
        
        cube->red[rot_edge_row[i + 1]][rot_edge_col[i + 1]] = temp_edge;
        cube->red[rot_corner_row[i + 1]][rot_corner_col[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->yellow[i][0];
        char temp_faces1 = cube->green[i][0];

        cube->green[i][0] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->white[i][0];

        cube->white[i][0] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->blue[2 - i][0];

        cube->blue[2 - i][0] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->yellow[i][0];

        cube->yellow[i][0] = temp_faces;
    }
}

// Functions that executes a F move on the cube struct
void F_move(Cube * cube)
{
    // Variables
    int i;
    char temp_edge = cube->green[rot_edge_row[0]][rot_edge_col[0]];
    char temp_corner = cube->green[rot_corner_row[0]][rot_corner_col[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->green[rot_edge_row[i + 1]][rot_edge_col[i + 1]];
        char temp_corner1 = cube->green[rot_corner_row[i + 1]][rot_corner_col[i + 1]];
        
        cube->green[rot_edge_row[i + 1]][rot_edge_col[i + 1]] = temp_edge;
        cube->green[rot_corner_row[i + 1]][rot_corner_col[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->yellow[2][i];
        char temp_faces1 = cube->orange[i][2];

        cube->orange[i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->white[0][2 - i];

        cube->white[0][2 - i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->red[2 - i][2];

        cube->red[2 - i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->yellow[2][i];

        cube->yellow[2][i] = temp_faces;
    }
}

// Functions that executes a M move on the cube struct
void M_move(Cube * cube)
{
    // Rotates pieces across faces 
    for(int i = 0; i < 3; i++)
    {
        char temp_faces = cube->yellow[i][1];
        char temp_faces1 = cube->green[i][1];

        cube->green[i][1] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->white[i][1];

        cube->white[i][1] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->blue[2 - i][1];

        cube->blue[2 - i][1] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->yellow[i][1];

        cube->yellow[i][1] = temp_faces;
    }

}

// Functions that executes a D move on the cube struct
void D_move(Cube * cube)
{
    // Variables
    int i;
    char temp_edge = cube->white[rot_edge_row[0]][rot_edge_col[0]];
    char temp_corner = cube->white[rot_corner_row[0]][rot_corner_col[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->white[rot_edge_row[i + 1]][rot_edge_col[i + 1]];
        char temp_corner1 = cube->white[rot_corner_row[i + 1]][rot_corner_col[i + 1]];
        
        cube->white[rot_edge_row[i + 1]][rot_edge_col[i + 1]] = temp_edge;
        cube->white[rot_corner_row[i + 1]][rot_corner_col[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->blue[2][2 - i];
        char temp_faces1 = cube->red[2][i];

        cube->red[2][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->green[2][i];

        cube->green[2][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->orange[2][2 - i];

        cube->orange[2][2 - i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->blue[2][2 - i];

        cube->blue[2][2 - i] = temp_faces;
    }
}

// Functions that executes a E move on the cube struct
void E_move(Cube * cube)
{
    // Rotates pieces across faces
    for(int i = 0; i < 3; i++)
    {
        char temp_faces = cube->blue[1][2 - i];
        char temp_faces1 = cube->red[1][i];

        cube->red[1][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->green[1][i];

        cube->green[1][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->orange[1][2 - i];

        cube->orange[1][2 - i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->blue[1][2 - i];

        cube->blue[1][2 - i] = temp_faces;
    }
}

// Functions that executes a U prime move on the cube struct
void U_Prime_move(Cube * cube)
{
    // Varialbes
    int i;
    char temp_edge = cube->yellow[rot_edge_row_inv[0]][rot_edge_col_inv[0]];
    char temp_corner = cube->yellow[rot_corner_row_inv[0]][rot_corner_col_inv[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->yellow[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]];
        char temp_corner1 = cube->yellow[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]];
        
        cube->yellow[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]] = temp_edge;
        cube->yellow[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->blue[0][2 - i];
        char temp_faces1 = cube->red[0][i];

        cube->red[0][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->green[0][i];

        cube->green[0][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->orange[0][2 - i];

        cube->orange[0][2 - i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->blue[0][2 - i];

        cube->blue[0][2 - i] = temp_faces;
    }
}

// Functions that executes a F prime move on the cube struct
void F_Prime_move(Cube * cube)
{
    // Variables
    int i;
    char temp_edge = cube->green[rot_edge_row_inv[0]][rot_edge_col_inv[0]];
    char temp_corner = cube->green[rot_corner_row_inv[0]][rot_corner_col_inv[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->green[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]];
        char temp_corner1 = cube->green[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]];
        
        cube->green[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]] = temp_edge;
        cube->green[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->yellow[2][i];
        char temp_faces1 = cube->red[2 - i][2];

        cube->red[2 - i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->white[0][2 - i]; 

        cube->white[0][2 - i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->orange[i][2];

        cube->orange[i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->yellow[2][i];

        cube->yellow[2][i] = temp_faces;
    }
}

// Functions that executes a R prime move on the cube struct
void R_Prime_move(Cube * cube)
{
    // Variables
    int i;
    char temp_edge = cube->orange[rot_edge_row[0]][rot_edge_col[0]];
    char temp_corner = cube->orange[rot_corner_row[0]][rot_corner_col[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->orange[rot_edge_row[i + 1]][rot_edge_col[i + 1]];
        char temp_corner1 = cube->orange[rot_corner_row[i + 1]][rot_corner_col[i + 1]];
        
        cube->orange[rot_edge_row[i + 1]][rot_edge_col[i + 1]] = temp_edge;
        cube->orange[rot_corner_row[i + 1]][rot_corner_col[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->yellow[i][2];
        char temp_faces1 = cube->green[i][2];

        cube->green[i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->white[i][2];

        cube->white[i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->blue[2 - i][2];

        cube->blue[2 - i][2] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->yellow[i][2];

        cube->yellow[i][2] = temp_faces;
    }

    
}

// Functions that executes a L prime move on the cube struct
void L_Prime_move(Cube * cube)
{
    // Variables
    int i;
    char temp_edge = cube->red[rot_edge_row_inv[0]][rot_edge_col_inv[0]];
    char temp_corner = cube->red[rot_corner_row_inv[0]][rot_corner_col_inv[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->red[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]];
        char temp_corner1 = cube->red[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]];
        
        cube->red[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]] = temp_edge;
        cube->red[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->yellow[i][0];
        char temp_faces1 = cube->blue[2 - i][0];

        cube->blue[2 - i][0] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->white[i][0];

        cube->white[i][0] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->green[i][0];

        cube->green[i][0] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->yellow[i][0];

        cube->yellow[i][0] = temp_faces;
    }
}

// Functions that executes a M prime move on the cube struct
void M_Prime_move(Cube * cube)
{   
    // Rotates pieces across faces
    for(int i = 0; i < 3; i++)
    {
        char temp_faces = cube->yellow[i][1];
        char temp_faces1 = cube->blue[2 - i][1];

        cube->blue[2 - i][1] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->white[i][1];

        cube->white[i][1] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->green[i][1];

        cube->green[i][1] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->yellow[i][1];

        cube->yellow[i][1] = temp_faces;
    }
}

// Functions that executes a D prime move on the cube struct
void D_Prime_move(Cube * cube)
{
    // Variables
    int i;
    char temp_edge = cube->white[rot_edge_row_inv[0]][rot_edge_col_inv[0]];
    char temp_corner = cube->white[rot_corner_row_inv[0]][rot_corner_col_inv[0]];

    // Rotates pieces on face
    for(i = 0; i < 4; i++)
    {   
        char temp_edge1 = cube->white[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]];
        char temp_corner1 = cube->white[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]];
        
        cube->white[rot_edge_row_inv[i + 1]][rot_edge_col_inv[i + 1]] = temp_edge;
        cube->white[rot_corner_row_inv[i + 1]][rot_corner_col_inv[i + 1]] = temp_corner;

        temp_edge = temp_edge1;
        temp_corner = temp_corner1;
    }  

    // Rotates pieces across faces 
    for(i = 0; i < 3; i++)
    {
        char temp_faces = cube->blue[2][2 - i];
        char temp_faces1 = cube->orange[2][2 - i];

        cube->orange[2][2 - i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->green[2][i];

        cube->green[2][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->red[2][i];

        cube->red[2][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->blue[2][2 - i];

        cube->blue[2][2 - i] = temp_faces;
    }
}

// Functions that executes a E prime move on the cube struct
void E_Prime_move(Cube * cube)
{
    // Rotates pieces across faces
    for(int i = 0; i < 3; i++)
    {
        char temp_faces = cube->blue[1][2 - i];
        char temp_faces1 = cube->orange[1][2 - i];

        cube->orange[1][2 - i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->green[1][i];

        cube->green[1][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->red[1][i];

        cube->red[1][i] = temp_faces;
        temp_faces = temp_faces1;
        temp_faces1 = cube->blue[1][2 - i];

        cube->blue[1][2 - i] = temp_faces;
    }
}

// Functions that prints out cube
void printCube(Cube * cube)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        printf("    ");
        for (j = 0; j < 3; j++)
        {
            color(cube->yellow[i][j]);
            printf("%c", cube->yellow[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < 3; i++)
    {
        
        for (j = 0; j < 3; j++)
        {
            color(cube->red[i][j]);
            printf("%c", cube->red[i][j]);  
        }
        
        printf(" ");

        for (j = 0; j < 3; j++)
        {
            
            color(cube->green[i][j]);
            printf("%c", cube->green[i][j]);
        }
        
        printf(" ");

        for (j = 0; j < 3; j++)
        {
            
            color(cube->orange[i][2 - j]);
            printf("%c", cube->orange[i][2 - j]);
        }
            
        printf(" ");

        for (j = 0; j < 3; j++)
        {
            
            color(cube->blue[i][2 -  j]);
            printf("%c", cube->blue[i][2 -  j]);
        }

        printf(" ");

        printf("\n");
    }

    for (i = 0; i < 3; i++)
    {
        printf("    ");
        for (j = 0; j < 3; j++)
        {
            color(cube->white[i][j]);
            printf("%c", cube->white[i][j]);
        }
        printf("\n");
    }

    printf("\e[0;37m");
}

// Function that when given a string executes an algorithm based on charactors 
void alg_execute(Cube * cube, char * alg)
{
    // Determine algorithm langth
    int length = strlen(alg);

    // Run through the algorithm and execute a move based on charactor given
    for(int i = 0; i < length; i++)
    {
        switch(alg[i])
        {
            case 'R':
                R_move(cube);
                break;
            
            case 'r':
                R_Prime_move(cube);
                break;
            
            case 'L':
                L_move(cube);
                break;
            
            case 'l':
                L_Prime_move(cube);
                break;
            
            case 'U':
                U_move(cube);
                break;
            
            case 'u':
                U_Prime_move(cube);
                break;
            
            case 'F':
                F_move(cube);
                break;
            
            case 'f':
                F_Prime_move(cube);
                break;
            
            case 'M':
                M_move(cube);
                break;
            
            case 'm':
                M_Prime_move(cube);
                break;

            case 'D':
                D_move(cube);
                break;
            
            case 'd':
                D_Prime_move(cube);
                break;    

            case 'X':
                L_Prime_move(cube);
                M_Prime_move(cube);
                R_move(cube);
                break;
            
            case 'x':
                L_move(cube);
                M_move(cube);
                R_Prime_move(cube);
                break; 

            case 'Y':
                U_move(cube);
                E_Prime_move(cube);
                D_Prime_move(cube);
                break;
            
            case 'y':
                U_Prime_move(cube);
                E_move(cube);
                D_move(cube);
                break;    
        }
    }
}

// Functions that when given a string returns an algorithm based on the string name
char * alg_find(char * alg)
{
    // PLL algs
    if(strcmp(alg, "Ja_perm") == 0) return "luLFluLULfllULU";
    if(strcmp(alg, "Jb_perm") == 0) return "RUrfRUrurFRRuru";
    if(strcmp(alg, "T_perm") == 0) return "RUrurFRRuruRUrf";
    if(strcmp(alg, "F_perm") == 0) return "rufRUrurFRRuruRUrUR";
    if(strcmp(alg, "Y_perm") == 0) return "FRuruRUrfRUrurFRf";
    if(strcmp(alg, "Ua_perm") == 0) return "MMUMUUmUMM";
    if(strcmp(alg, "Ub_perm") == 0) return "MMuMUUmuMM";
    if(strcmp(alg, "H_perm") == 0) return "MMUMMUUMMUMM";
    if(strcmp(alg, "Z_perm") == 0) return "mUMMUMMUmUUMMu";
    if(strcmp(alg, "Ga_perm") == 0) return "RRUrUruRuRRuDrURd";
    if(strcmp(alg, "Gb_perm") == 0) return "ruRUdRRUrURuRuRRD";
    if(strcmp(alg, "Gc_perm") == 0) return "RRuRuRUrURRUdRurD";
    if(strcmp(alg, "Gd_perm") == 0) return "RUruDRRuRurUrURRd";
    if(strcmp(alg, "Ra_perm") == 0) return "RuruRURDruRdrUUr";
    if(strcmp(alg, "Rb_perm") == 0) return "RRFRURurfRUUrUUR";
    if(strcmp(alg, "Na_perm") == 0) return "RUrURUrfRUrurFRRurUURur";
    if(strcmp(alg, "Nb_perm") == 0) return "rURurfuFRUrFrfRuR";
    if(strcmp(alg, "V_perm") == 0) return "rUruYrfRRurUrFRFy";
    if(strcmp(alg, "E_perm") == 0) return "xlULdluLDluLdlULDX";
    if(strcmp(alg, "Aa_perm") == 0) return "XLLDDluLDDlUl";
    if(strcmp(alg, "Ab_perm") == 0) return "xLLDDLUlDDLuL";
    
    // C-OLL algs
    if(strcmp(alg, "21") == 0) return "RUUruRUruRur";
    if(strcmp(alg, "22") == 0) return "RUURRuRRuRRUUR";
    if(strcmp(alg, "23") == 0) return "RRdRUUrDRUUR";
    if(strcmp(alg, "24") == 0) return "mRUruMrFRf";
    if(strcmp(alg, "25") == 0) return "fmRUruMrFR";
    if(strcmp(alg, "26") == 0) return "RUUruRur";
    if(strcmp(alg, "27") == 0) return "RUrURUUr";

    // Yellow cross algs
    if(strcmp(alg, "Arrow") == 0) return "FRUruRUruf";
    if(strcmp(alg, "Line") == 0) return "FRUruf";
    if(strcmp(alg, "Empty") == 0) return "FRUruRUrufUFRUruf";

    // Gen algs
    if(strcmp(alg, "S_move") == 0)   return "RUru";

    // White cross algs
    if(strcmp(alg, "R_C") == 0)   return "RUr";
    if(strcmp(alg, "L_C") == 0)   return "luL";
    if(strcmp(alg, "D_C") == 0)   return "fRUr";
    if(strcmp(alg, "U_C") == 0)   return "UfuFRUr";
}

// Changes text color based on current charactor passed in
void color(char a)
{
    switch(a)
    {
        case 'R': 
            printf("\e[0;91m");
            break;

        case 'W': 
            printf("\e[0;97m");
            break;

        case 'O': 
            printf("\e[30;31m");
            break;

        case 'Y': 
            printf("\e[0;93m");
            break;

        case 'G': 
            printf("\e[0;92m");
            break;

        case 'B': 
            printf("\e[94m");
            break;
    }
}

// Initializes cube struct
Cube * initials_cube()
{
    // Allocates space for the cube
    Cube * cube = malloc(sizeof(Cube));

    // Allocate space for the cube faces
    cube->white = calloc(3, sizeof(char*));
    cube->yellow = calloc(3, sizeof(char*));
    cube->blue = calloc(3, sizeof(char*));
    cube->green = calloc(3, sizeof(char*));
    cube->orange = calloc(3, sizeof(char*));
    cube->red = calloc(3, sizeof(char*));

    for(int i = 0; i < 3; i++)
    {
        cube->white[i] = calloc(3, sizeof(char));
        cube->yellow[i] = calloc(3, sizeof(char));
        cube->blue[i] = calloc(3, sizeof(char));
        cube->green[i] = calloc(3, sizeof(char));
        cube->orange[i] = calloc(3, sizeof(char));
        cube->red[i] = calloc(3, sizeof(char));
    }

    // Fill initial cube
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cube->white[i][j] = 'W';
            cube->yellow[i][j] = 'Y';
            cube->blue[i][j] = 'B';
            cube->green[i][j] = 'G';
            cube->orange[i][j] = 'O';
            cube->red[i][j] ='R';
        }
    }

    // Return created cube
    return cube;
}

// Orients cube so each faces is in the correct color
void Orient(Cube * cube)
{
    int i, j;

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            alg_execute(cube, "X");
            if(cube->white[1][1] == 'W') break;
        }

        if(cube->white[1][1] == 'W') break;
        alg_execute(cube, "Y");
    }   

    for(i = 0; i < 4; i++)
    {
        if(cube->green[1][1] == 'G') break;
        alg_execute(cube, "Y");
    }


}

// Returns 1 if cube is solved, returns 0 if not
int Solved(Cube * cube)
{
    int i, j, flag = 1;

    Orient(cube);

    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(cube->white[i][j] != 'W') flag = 0;

     for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(cube->green[i][j] != 'G') flag = 0;

     for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(cube->blue[i][j] != 'B') flag = 0;

     for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(cube->orange[i][j] != 'O') flag = 0;

     for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(cube->red[i][j] != 'R') flag = 0;

     for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(cube->yellow[i][j] != 'Y') flag = 0;

    return flag;

}

// Solves the white cross
void W_C(Cube * cube)
{
    int i, j, k, m, count = 0;

    for(i = 0; i < 4; i++)
    {
        count = 0;
        if(cube->white[rot_edge_row[i]][rot_edge_col[i]] == 'W')
        {
            for(j = 0; j < i; j++)
            {
                alg_execute(cube,  "Y");
                printf("Y");
            }

            while(cube->white[rot_edge_row[0]][rot_edge_col[0]] == 'W' && count < 4)
            {
                alg_execute(cube,  "F");
                printf("F");
                count++;
            }

            if(cube->white[rot_edge_row[0]][rot_edge_col[0]] == 'W')
            {
                printf("UFF");
                alg_execute(cube,  "UFF");
            }
                

            for(j = 0; j < i; j++)
            {
                alg_execute(cube,  "y");
                printf("y");
            }
        }
    } 

    count = 0;

    for(i = 0; i < 4 && count < 4; i++)
    {
        for(j = 0; j < 5 && count < 4; j++)
        {
            if(j != 4)
            {
                for(k = 0; k < 4 && count < 4; k++)
                {
                    if(cube->green[rot_edge_row[k]][rot_edge_col[k]] == 'W')
                    {
                        switch (k)
                        {
                            case 0:
                                alg_execute(cube,  alg_find("U_C"));
                                printf(alg_find("U_C"));
                                break;

                            case 1:
                                alg_execute(cube,  alg_find("R_C"));
                                printf(alg_find("R_C"));
                                break;

                            case 2:
                                alg_execute(cube,  alg_find("D_C"));
                                printf(alg_find("D_C"));
                                break;

                            case 3:
                                alg_execute(cube,  alg_find("L_C"));
                                printf(alg_find("L_C"));
                                break;
                        }

                        while(cube->green[0][1] != cube->green[1][1])
                        {
                            alg_execute(cube,  "Yu");
                            printf("Yu");
                        }

                        alg_execute(cube,  "FF");
                        printf("FF");
                        count++;
                    }

                }
                alg_execute(cube,  "Y");
                printf("Y");
            }

            if(j == 4 && count < 4)
            {
                for(k = 0; k < 4; k++)
                {
                    if(cube->yellow[rot_edge_row[k]][rot_edge_col[k]] == 'W')
                    {
                        for(m = 0; m < k + 2; m++)
                        {
                            alg_execute(cube,  "u");
                            printf("u");
                        }

                        while(cube->green[0][1] != cube->green[1][1])
                        {
                            alg_execute(cube,  "Yu");
                            printf("Yu");
                        }

                        alg_execute(cube,  "FF");
                        count++;
                        printf("FF");
                        break;
                            
                    }                    
                }
            }
        }
    }
}
