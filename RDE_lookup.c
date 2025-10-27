    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    enum {
        minPt = 0,
        maxPt = 3,
        minTt = 0,
        maxTt = 5,
        minWb = 0,
        maxWb = 10
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
        char line[256];
        FILE *fp = fopen("STtest.csv", "r");

        if(fp == NULL) {
            printf("Error opening file\n");
            return;
        }
        
        while (fgets(line, sizeof(line), fp) != NULL) {
            float Pt_in, Tt_in, Fuel_frac, mdot_out Pt_out, Tt_out;
            int n = sscanf(line, "%f,%f,%f,%f,%f", &Pt_in, &Tt_in, &Fuel_frac, &mdot_out, &Pt_out, &Tt_out);
            if (n != 5) {
                printf("⚠️  Skipping malformed line: %s", line);
                continue;
            }
            sscanf(line, "%f,%f,%f,%f,%f", &Pt_in, &Tt_in, &FuelFrac, &Pt_out, &Tt_out);
            int i = (int)(Pt_in - minPt);
            int j = (int)(Tt_in - minTt);
            int k = (int)(Wb - minWb);
            printf("i=%f, j=%f, k=%f, output = %f, %f\n", Pt_in, Tt_in, FuelFrac,  Pt_out, Tt_out);
            matrix[i][j][k] = createOutput(Pt_out, Tt_out);
        }
    }

    struct output testMatrix[3][3][3];
    void testSetUp() {   
    //Intitialize matrix with             Pt    Tt  
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

    setUp();
    printf("\n Pt = %.1f, Tt = %.1f",
    matrix[1][2][0].Pt, matrix[1][2][0].Tt);
    return 0;
}