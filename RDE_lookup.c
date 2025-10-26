    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    enum {
        minPt = 0,
        maxPt = 10,
        minTt = 0,
        maxTt = 300,
        minWb = 0,
        maxWb = 500
    };

    struct output {
        float Pt;
        float Tt;
    };

    struct output createOutput(float Pt, float Tt){
        struct output out;
        out.Pt = Pt;
        out.Tt = Tt;
        return out;
    }

    //parses matlabb output "Pt = Tt" and creates a struct
    struct output split_matlab_output(char *matlab_output){
        char *Pt, *Tt;
        Pt = strtok(matlab_output, "=");
        Tt = strtok(NULL, "=");
        while (*Pt == ' ') Pt++;
        while (*Tt == ' ') Tt++;
        return createOutput(atof(Pt), atof(Tt));
    }

    struct output matrix[maxPt - minPt + 1][maxTt - minTt + 1][maxWb - minWb + 1];
    void setUp() {

    }

    struct output testMatrix[3][3][3];
    void testSetUp() {   
    //Intitialize matrix with          Pt    Tt  
    testMatrix[0][0][0] = (struct output){0.0, 0.0};
    testMatrix[0][1][0] = (struct output){0.0, 0.0};
    testMatrix[0][2][0] = (struct output){5.0, 6.0};
    
    testMatrix[1][0][0] = (struct output){1.0, 2.0};
    testMatrix[1][1][0] = (struct output){4.0, 5.0};
    testMatrix[1][2][0] = (struct output){7.0, 8.0};
    
    testMatrix[2][0][0] = (struct output){10.0, 11.0};
    testMatrix[2][1][0] = (struct output){13.0, 14.0};
    testMatrix[2][2][0] = (struct output){16.0, 17.0};
}

int main() {
    //testing matlab input (Pt = Tt)
    char str[] = "100 = 200";

    //tests the split function
    struct output test = split_matlab_output(str);
    printf("Pt = %.1f, Tt = %.1f",
    test.Pt, test.Tt);

    //tests the matrix setup
    testSetUp();
    printf("\n Pt = %.1f, Tt = %.1f",
    testMatrix[1][2][0].Pt, testMatrix[1][2][0].Tt);


    return 0;
}