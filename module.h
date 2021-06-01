int myModule(int dividend, int divisor)
{
	const int quotient = dividend / divisor;
	const int remainder = dividend - (quotient * divisor);
	return (remainder < 0) ? remainder + divisor : remainder;
}
