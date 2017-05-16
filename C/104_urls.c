#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////

typedef struct Web {
    char    full_name[41];
    char    short_name[21];
    char    url[121];
} Website;


////////////////////////////////////////

void initSite(Website *site) {
    scanf("%s", site->short_name); getchar();
    scanf("%s", site->full_name); getchar();
    scanf("%s", site->url); getchar();
}

void printSite(Website *site) {
    printf("%-19s %-39s %s\n",
           site->short_name,
           site->full_name,
           site->url);
}


void sortSites(Website *sites, int cnt) {
    int i, j;
    Website tmp_site;
    for (i = 0; i < cnt-1; ++i) {
        for (j = 0; j < cnt-i-1; ++j) {
            if (strcmp(sites[j].short_name, sites[j+1].short_name) > 0) {
                tmp_site = sites[j+1];
                sites[j+1] = sites[j];
                sites[j] = tmp_site;
            }
        }
    }
}

///////////////////////////////////////

void main(void) {

    int n, i;
    scanf("%d", &n); getchar();

    Website *sites = (Website *)malloc(n*sizeof(Website));
    Website *site = sites;

    for (i = 0, site = sites; i < n; ++i, ++site) {
        initSite(site);
    }
    for (i = 0, site = sites; i < n; ++i, ++site) {
        printSite(site);
    }

    putchar('\n');

    sortSites(sites, n);
    for (i = 0, site = sites; i < n; ++i, ++site) {
        printSite(site);
    }



    for (i = 0, site = sites; i < n; ++i, ++site) { free(site); }

}
