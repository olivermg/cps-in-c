
int main( int argc, char* argv[] )
{
	int mul( int n ) {
		int add( int m, int n ) {
			return m + n;
		}

		return add( n ) * n;
	}

	return mul( 3 );
}

