package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

const (
	maxN = 110
)

var F [maxN][5][2]int
var P [maxN][11]int

func main() {
	fsc := NewFastScanner()
	N := fsc.NextInt()
	for i := 0; i < N; i++ {
		for j := 0; j < 5; j++ {
			for k := 0; k < 2; k++ {
				F[i][j][k] = fsc.NextInt()
			}
		}
	}
	for i := 0; i < N; i++ {
		for j := 0; j < 11; j++ {
			P[i][j] = fsc.NextInt()
		}
	}
	result := -10000000000
	for bit := 1; bit < (1 << 10); bit++ {
		open := make([]int, 0)
		for i := 0; i < 10; i++ {
			if ((bit >> uint(i)) & 1) == 1 {
				open = append(open, 1)
			} else {
				open = append(open, 0)
			}
		}
		sum := 0
		for i := 0; i < N; i++ {
			cnt := 0
			for j := 0; j < 5; j++ {
				for k := 0; k < 2; k++ {
					if F[i][j][k] == 1 && open[2*j+k] == 1 {
						cnt++
					}
				}
			}
			sum += P[i][cnt]
		}
		result = IntMax(result, sum)
	}
	fmt.Println(result)
}

//template
type FastScanner struct {
	r   *bufio.Reader
	buf []byte
	p   int
}

func NewFastScanner() *FastScanner {
	rdr := bufio.NewReaderSize(os.Stdin, 1024)
	return &FastScanner{r: rdr}
}
func (s *FastScanner) Next() string {
	s.pre()
	start := s.p
	for ; s.p < len(s.buf); s.p++ {
		if s.buf[s.p] == ' ' {
			break
		}
	}
	result := string(s.buf[start:s.p])
	s.p++
	return result
}
func (s *FastScanner) NextLine() string {
	s.pre()
	start := s.p
	s.p = len(s.buf)
	return string(s.buf[start:])
}
func (s *FastScanner) NextInt() int {
	v, _ := strconv.Atoi(s.Next())
	return v
}
func (s *FastScanner) NextInt64() int64 {
	v, _ := strconv.ParseInt(s.Next(), 10, 64)
	return v
}

func (s *FastScanner) pre() {
	if s.p >= len(s.buf) {
		s.readLine()
		s.p = 0
	}
}
func (s *FastScanner) readLine() {
	s.buf = make([]byte, 0)
	for {
		l, p, e := s.r.ReadLine()
		if e != nil {
			panic(e)
		}
		s.buf = append(s.buf, l...)
		if !p {
			break
		}
	}
}

//Max,Min
func IntMax(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func Int64Max(a, b int64) int64 {
	if a < b {
		return b
	}
	return a
}
func Float64Max(a, b float64) float64 {
	if a < b {
		return b
	}
	return a
}

func IntMin(a, b int) int {
	if a > b {
		return b
	}
	return a
}

func Int64Min(a, b int64) int64 {
	if a > b {
		return b
	}
	return a
}
func Float64Min(a, b float64) float64 {
	if a > b {
		return b
	}
	return a
}

//Gcd
func IntGcd(a, b int) int {
	if a < b {
		b, a = a, b
	}
	if b == 0 {
		return a
	}
	return IntGcd(b, a%b)
}
func Int64Gcd(a, b int64) int64 {
	if a < b {
		b, a = a, b
	}
	if b == 0 {
		return a
	}
	return Int64Gcd(b, a%b)
}

func IntAbs(a int) int {
	if a < 0 {
		a *= -1
	}
	return a
}

func Int64Abs(a int64) int64 {
	if a < 0 {
		a *= -1
	}
	return a
}
