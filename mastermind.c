/* mastermind - utilities for the mastermind board game
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

#include	"mastermind.h"

Score
eval(Digit a[CODELEN], Digit b[CODELEN])
{
	unsigned	i, afreq[CODERADIX], bfreq[CODERADIX];
	Score	score;

	memset(afreq, 0, sizeof(afreq));
	memset(bfreq, 0, sizeof(bfreq));

	for (i = score.b = 0; i < CODERADIX; ++i) {
		++afreq[a[i]];
		++bfreq[b[i]];
		if (a[i] == b[i])
			++score.b;
	}

	for (i = 0, score.w = -score.b; i < CODERADIX; ++i)
		score.w += (afreq[i] < bfreq[i]) ? afreq[i] : bfreq[i];

	return score;
}

void
fscancode(Digit code[CODELEN], FILE *stream)
{
	Digit	*end;

	for (end = code + CODELEN; code < end; ++code) {
		if (fscanf(stream, "%u", code) < 1) {
			exit(EXIT_FAILURE);
		}
	}
}

void
fprintcode(Digit code[CODELEN], FILE *stream)
{
	Digit	*end;

	for (end = code + CODELEN; code < end; ++code) {
		if (fprintf(stream, "%u\t", *code) < 0)
			exit(EXIT_FAILURE);
	}
	if (putc('\n', stream) == EOF)
		exit(EXIT_FAILURE);
}

void
fscanscore(Score *score, FILE *stream)
{
	if (fscanf(stream, "%u%u", &score->b, &score->w) < 2) {
		exit(EXIT_FAILURE);
	}
}

void
fprintscore(Score *score, FILE *stream)
{
	if (fprintf(stream, "%u\t%u\n", score->b, score->w) < 0) {
		exit(EXIT_FAILURE);
	}
}
