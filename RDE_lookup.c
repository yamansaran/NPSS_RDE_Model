    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    #define minPt 1000
    #define maxPt 1008
    #define minTt 540
    #define maxTt 550
    #define minFuelFrac 0.2
    #define maxFuelFrac 0.25
    #define fuelFracStep 0.025
    #define maxLines 10000000


    static char matrix[maxPt - minPt + 1][maxTt - minTt + 1][(int)((maxFuelFrac - minFuelFrac) / fuelFracStep) + 1][50];
    static double Pt_grid[maxPt - minPt + 1],
           Tt_grid[maxTt - minTt + 1],
           W_grid[maxLines];

    int W_size = 0;
    void setUp() {
        char line[256];
        FILE *fp = fopen("burner_lookup_table.csv", "r");

        if(fp == NULL) {
            printf("Error opening file\n");
            return;
        }
        int count = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            float Pt_in, Tt_in, Fuel_frac, mdot_out, Pt_out, Tt_out;
            int n = sscanf(line, "%f,%f,%f,%f,%f,%f", &Pt_in, &Tt_in, &Fuel_frac, &mdot_out, &Pt_out, &Tt_out);
            if (n != 6) {
                printf("⚠️  Skipping malformed line: %s", line);
                continue;
            }
            //printf("Read line: Pt_in=%.2f, Tt_in=%.2f, Fuel_frac=%.2f, mdot_out=%.2f, Pt_out=%.2f, Tt_out=%.2f\n",
            //       Pt_in, Tt_in, Fuel_frac, mdot_out, Pt_out, Tt_out);
            
            char output[50];
            sprintf(output, "%d=%d", (int)Pt_out, (int)Tt_out);
            strcpy(matrix[(int)Pt_in - minPt][(int)Tt_in - minTt][(int)round(-(Fuel_frac - maxFuelFrac) / fuelFracStep)], output);
            Pt_grid[count] = Pt_in;
            Tt_grid[count] = Tt_in;
            W_grid[count] = mdot_out;

            //printf("Stored in matrix[%d][%d][%d]: %s\n",
            //       (int)Pt_in - minPt, (int)Tt_in - minTt, (int)round(-(Fuel_frac - maxFuelFrac) / fuelFracStep), output);
            //printf("Grids: Pt_grid[%d]=%.2f, Tt_grid[%d]=%.2f, W_grid[%d]=%.2f\n",
            //       count, Pt_grid[count], count, Tt_grid[count], count, W_grid[count]);
            count++;
        }
        W_size = count;
        fclose(fp);
        printf("Finished reading file\n");
    }
    int get_W_grid_size() {
        return W_size;
    }
    int get_Pt_grid_size() {
        return maxPt - minPt + 1;
    }
    int get_Tt_grid_size() {
        return maxTt - minTt + 1;
    }
    double get_W_grid(int index) {
        return W_grid[index];
    }
    double get_Pt_grid(int index) {
        return Pt_grid[index];
    }
    double get_Tt_grid(int index) {
        return Tt_grid[index];
    }
    const char* get_RDE_data(int Pt_idx, int Tt_idx, int Fuel_frac_idx) {
        return matrix[Pt_idx][Tt_idx][Fuel_frac_idx];
    }

int main() {
    setUp();
    return 0;
}