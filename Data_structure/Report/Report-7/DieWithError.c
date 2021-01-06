//
//  DieWithError.c
//  Data_structure
//
//  Created by Seokhwan Kwon on 2020/12/19.
//  Copyright © 2020 Seokhwan Kwon. All rights reserved.
//  20184646 권석환

#include "TCP_Server.h"
#include <stdio.h>      // for perror()
#include <stdlib.h>     // for exit()

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
