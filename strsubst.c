#include <stdio.h>

int main(int argc, char** argv) {
    char *conditionalFormat = "If %s %s %s %s %s";
    char *ast = "MPD@availabilityStartTime";
    char *mpdtype = "MPD@MPDType dynamic";
    char *enfType = "MUST";
    char *coperator = "PRESENT";
    char result[100];
    sprintf(result, conditionalFormat, mpdtype, ast, enfType, coperator);

    const char *val = "24";
    const char *fval = "24.5353";
    printf("%d %f\n", atoi(val), atof(fval));

    printf("%s", result);
    return sizeof(result);
}
