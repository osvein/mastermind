/* mastermind-break - codebreaker for the mastermind board game
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

#include	<stdlib.h>
#include	<stdio.h>

#include	"mastermind.h"
#include	"io.h"
#include	"break.h"

typedef	struct Codenode	Codenode;

struct Codenode {
	Digit	code[CODELEN];
	unsigned	next;
};

Codenode	guesspool[CODEPERMC];
unsigned	firstguess;

static void
updatepool(Digit guess[CODELEN], Score score)
{
	unsigned	*i;

	i = &firstguess;
	while (*i < CODEPERMC) {
		Score	s;

		s = eval(guesspool[*i].code, guess);
		if (s.b == score.b && s.w == score.w) {
			i = &guesspool[*i].next;
		} else {
			unsigned	newnext;

			newnext = guesspool[*i].next;
			guesspool[*i].next = CODEPERMC + 1;
			*i = newnext;
		}
	}
}

unsigned
countelims(Digit guess[CODELEN], Score score)
{
	unsigned	count;
	Codenode	*node;

	for (node = guesspool + firstguess, count = 0; node < guesspool + CODEPERMC; node = guesspool + node->next) {
		Score	s;

		s = eval(node->code, guess);
		if (s.b != score.b || s.w != score.w)
			++count;
	}
	return count;
}

int
main(void)
{
	Score score;
	Codenode	*max;
	unsigned	i;

	/* fill guesspool */
	for (guesspool[0].next = i = 1; i < CODEPERMC; ++i) {
		char	carry;
		unsigned	j;

		for (j = 0, carry = 1; j < CODELEN; ++j)
			if ((guesspool[i].code[j] = guesspool[i - 1].code[j] + carry) < CODERADIX)
				carry = 0;
			else
				guesspool[i].code[j] = 0;
		guesspool[i].next = i + 1;
	}

	do {
		Codenode	*node;
		Value	maxval;

		for (node = guesspool, maxval = 0; node < guesspool + CODEPERMC; ++node) {
			Value	val;

			val = calcvalue(node->code);
			if (val > maxval || (val == maxval && node->next <= CODEPERMC)) {
				max = node;
				maxval = val;
			}
		}
		fprintcode(max->code, stdout);
		fscanscore(&score, stdin);
	} while (score.b < CODELEN && (updatepool(max->code, score), 1));
}
