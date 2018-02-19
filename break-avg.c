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

#include	"mastermind.h"
#include	"break.h"

Value
calcvalue(Digit code[CODELEN])
{
	unsigned long	sum;	/* watch out for overflows */
	unsigned	count;
	Score	score;

	for (score.b = count = sum = 0; score.b <= CODELEN; ++score.b) {
		unsigned	wmax;

		if ((wmax = CODELEN - score.b) == 1)
			wmax = 0;
		for (score.w = 0; score.w <= wmax; ++score.w) {
			sum += countelims(code, score);
			++count;
		}
	}
	return (Value)sum / count;
}
