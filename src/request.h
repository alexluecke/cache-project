#ifndef REQUEST_H
#define REQUEST_H

enum RequestType { READ, WRITE };

class Request {
	public:

		unsigned int address;
		unsigned int type;
		unsigned int data;

		Request(unsigned int a=0, unsigned int t=0, unsigned int d=0) {
			address = a;
			type = t;
			data = d;
		}

	private:

};

#endif
