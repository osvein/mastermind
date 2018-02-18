/* mastermind-make - codemaker for the mastermind board game
 * Copyright (c) 2018 Oskar Sveinsen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

#include	"mastermind.h"
#include	"io.h"

Digit	secret[CODELEN];

int
main(void)
{
	Digit	*i;
	Digit	code[CODELEN];
	Score	score;

	srand(time(NULL));
	for (i = secret; i < secret + CODERADIX; ++i)
		*i = rand() % CODERADIX;
	fprintcode(secret, stderr);

	do {
		fputs("guess:\t", stdout);
		if (fflush(stdout))
			exit(EXIT_FAILURE);
		fscancode(code, stdin);
		score = eval(code, secret);
		fputs("score:\t", stdout);
		fprintscore(&score, stdout);
	} while (score.b < CODELEN);

	return 0;
}
