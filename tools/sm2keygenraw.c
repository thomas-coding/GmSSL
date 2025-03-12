/*
 *  Copyright 2014-2022 The GmSSL Project. All Rights Reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the License); you may
 *  not use this file except in compliance with the License.
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 */


#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <gmssl/mem.h>
#include <gmssl/sm2.h>


static const char *usage = "output d,x,y\n";

static const char *options =
"Options\n"
"\n";

int sm2keygenraw_main(int argc, char **argv)
{
	int ret = 1;
	char *prog = argv[0];
	SM2_KEY key;
	FILE *outfp = stdout;
	int i = 0;

	argc--;
	argv++;

	while (argc > 0) {
		if (!strcmp(*argv, "-help")) {
			printf("usage: %s %s\n", prog, usage);
			printf("%s\n", options);
			ret = 0;
			goto end;
		} else {
			fprintf(stderr, "%s: illegal option '%s'\n", prog, *argv);
			goto end;
bad:
			fprintf(stderr, "%s: `%s` option value missing\n", prog, *argv);
			goto end;
		}

		argc--;
		argv++;
	}

	if (sm2_key_generate(&key) != 1) {
		fprintf(stderr, "%s: inner failure\n", prog);
		goto end;
	}
	sm2_key_print(stdout, 0, 0, "SM2:", &key);

	ret = 0;

end:
	gmssl_secure_clear(&key, sizeof(key));
	return ret;
}
