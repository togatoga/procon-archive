package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	fsc := NewFastScanner()
	N := fsc.Next()
	values := make([]int, 4)
	for i, val := range N {
		valNum, _ := strconv.Atoi(string(val))
		values[i] = valNum
	}
	for bit := 0; bit < (1 << 3); bit++ {
		sum := values[0]
		tmpBit := bit
		i := 1
		for j := 0; j < 3; j++ {
			if tmpBit%2 == 0 {
				sum += values[i]
			} else {
				sum -= values[i]
			}
			tmpBit /= 2
			i++
		}
		if sum == 7 {
			sigs := make([]string, 3)
			for i := 0; i < 3; i++ {
				if bit%2 == 0 {
					sigs[i] = "+"
				} else {
					sigs[i] = "-"
				}
				bit >>= 1
			}
			fmt.Print(values[0])
			for i := 0; i < 3; i++ {
				fmt.Print(sigs[i])
				fmt.Print(values[i+1])
			}
			fmt.Println("=7")
			break
		}
	}
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
