/******************************************************************************

Simple examples and questions in code as a skill development and debugging tool (IDE) familiarity exercise.

Very Short Version:
 Search for ##Q marks with questions and answer them in a seperate document. Submit.

Short Version:
 The ##Q marks are questions - answer them in order in a lab notes document. As
 you go save your changes and commit to your repo as evidence of your work.

Longer Version (recommended steps):
	2. Open this file in your IDE that *must* support debugging. (VS, CLion etc)
	3. Build and run this file. Make sure this works before going on.
	4. Create a lab-notes document for your answers. (Paste the questions provided
	   if you want, or discover them as you go.) Save and commit.
	4. Work your way through each of the file ##Q. marks in order.
	   - Work one section at a time. There are prprocessor directives that you can use to
			enable to code section by section
	   - Suggest committing your lab notes to your repo as you do each section (minimum).
		 This will make a good history of evidence for you!
	   - Suggest turning off the preprocessor directiver as you finish each section

There are quite a few questions (~33) but they are fairly simple.

As a top level view, here are the important sections (topics) in main()
	1. Warm up. Create a particle, set values, show to screen
	2. Get a particle with the values we pass to the function
	3. Set values in a particle that we already have
	4. Use a pointer to an existing particle
	5. Array of structs
	6. Struct pointer with new and delete for memory
	7. Array of pointers to structs

Written by Clinton Woodward <cwoodward@swin.edu.au>, James Bonner <jbonner@swin.edu.au>
 for COS30031 Games Programming

This file is for your personal study use only and must not be shared or made
 publicly available.

Updates
 2020-07-05: Cleanup, new questions and comment help.
 2024-07-20: Minor refactor, fixed typos & expression

*******************************************************************************/

#define SECTION1 false;
#define SECTION2 false;
#define SECTION3 false;
#define SECTION4 false;
#define SECTION5 false;
#define SECTION6 false;
#define SECTION7 false;

#include <iostream>

using namespace std;

// ##Q.1	What is the difference between a struct and a class?
struct Particle
{
	unsigned int age;
	int x;
	int y;
};

// ##Q.2	What are function declarations?
// ##Q2.1	Why and when are they are needed.
void showParticle(Particle);

// ##Q.3	Why are variable names not needed here? 
// ##Q3.1	Could you add variable names? Would that be good?
Particle createParticleWith(int, int, int);

void setParticleWith(Particle, int, int, int);

void showParticleArray(Particle*, int);

// ##Q.4	Does your IDE know if this method is used?
// If yes - how does it indicate this? (Colour? Tip? Other?)
void showParticleArray_2(Particle arr[], int size);

// Program entry point & main loop
int main()
{
#if SECTION1
	//Warm up. Create a particle, set values, show to screen
	cout << " << Section 1 >>" << endl;
	Particle a;
	// ##Q.5	un-initialised values ... what prints and why? 
	// NOTE: your IDE might be giving you a warning or error - if so note that in your answer (and fix).
	cout << "Q.5: a with uninitialised values ... ";
	showParticle(a);
	a.age = 0;
	a.x = 10;
	a.y = 20;
	cout << "Q.6: a with assigned values 0,10,20 ... ";
	showParticle(a); 
	// ##Q.6	Did this work as expected?

	// ##Q.7	Initialisation list - what are they?
	// Quicker then setting each part of the particle as above!
	// ##Q.7.1	Does your IDE suggest what the values are?
	Particle b = { 0,0,0 };
	cout << "Q.7: b with initialised values 0,0,0 ... ";
	showParticle(b);
#endif

#if SECTION2
	// 2. Get a particle with the values we pass to the function
	cout << " << Section 2 >>" << endl;
	Particle p1 = createParticleWith(1, 2, 3);
	cout << "Q.8: p1 with 1,2,3 ... ";
	showParticle(p1); 
	// ##Q.8	Should show age=1, x=1, y=2. Does it?

	p1 = createParticleWith(-1, 2, 3);
	cout << "Q.9: p1 with -1,2,3 ... ";
	// ##Q.9	Something odd here. What and why?
	// HINT: debug, inspect and look at data type details ...
	showParticle(p1); 
#endif

#if SECTION3
	// 3. Set values in a particle that we already have
	cout << " << Section 3 >>" << endl;
	// This compiles/runs, but ...
	Particle p1 = { 1,1,1 };
	setParticleWith(p1, 5, 6, 7);
	cout << "Q.10: b with 5,6,7 ... ";
	// ##Q.10	showParticle(p1) doesn't show 5,6,7 ... Why?
	// HINT: step-into functions with debugger and inspect values (and addresses)...
	showParticle(p1); 

#endif

#if SECTION4
	// 4. Use a pointer to an existing particle
	cout << " << Section 4 >>" << endl;
	Particle* p1_ptr;
	Particle p1 = createParticleWith(5, 5, 5);
	cout << "p1 with 5,5,5 ? ... ";
	showParticle(p1);
	p1_ptr = &p1;
	cout << "Address of p1:" << &p1 << endl;
	cout << "Value of p1_ptr:" << p1_ptr << endl;

	// Note that (*p1_ptr).age gets the p1.age value, so ...
	cout << "Q.11 and Q.12: Test results ..." << endl;
	(*p1_ptr).age == p1.age ? std::cout << " - TRUE!" : std::cout << " - False";
	cout << endl;
	(*p1_ptr).age == p1_ptr->age ? std::cout << " - TRUE!" : std::cout << " - False";
	cout << endl;
	// ##Q.11	What does -> mean?
	// ##Q.12	Do we need to put ( ) around *p1_ptr?
	// TIP: State what it means, or what it would mean if we didn't write it.

	// pass the dereferenced pointer as argument
	cout << "Q.13: p1 via dereferenced pointer ... ";
	showParticle((*p1_ptr));
	// ##Q.13	What is a dereferenced pointer?

	// update p1, ...
	p1 = createParticleWith(7, 7, 7);
	// Note: p1 is now a new particle struct with new values. So ...
	// ##Q.14	Is p1 stored on the heap or stack?
	// ##Q.15	What is p1_ptr pointing to now? (Has it changed?)
	// TIP: Use your IDE inspector to check the "address" of p1 and value of p1_ptr
	cout << "values of new p1 ? ... ";
	showParticle(p1);
	cout << "particle values at p1_ptr ?... ";
	showParticle((*p1_ptr));
	// ##Q.16	Is the current value of p1_ptr good or bad? Explain
#endif

#if SECTION5
	// 5. Array of structs
	cout << " << Section 5 >>" << endl;
	// NOTE: plain old array - not a fancy std::array
	Particle p_array1[3];
	p_array1[0] = createParticleWith(1, 2, 3);
	p_array1[1] = createParticleWith(4, 5, 6);
	p_array1[2] = createParticleWith(7, 8, 9);

	// ##Q.17	Uncomment the next code line - will it compile?
	//p_array1[3] = getParticleWith(0,0,0);
	// - If it compiles, does it run without errors?
	// ##Q.18	Does your IDE tell you of any issues? If so, how?
	// NOTE: Recommend you re-comment the line - it's not needed later

	// show that we can access one element of the array
	cout << "p_array[1] with 4,5,6 ... ";
	showParticle(p_array1[1]);
	// Array of pointers to structs
	showParticleArray(p_array1, 3);
	// ##Q.19	MAGIC NUMBER?! What is it? Is it bad? Explain!

	// Can we work out the length? Yes, but ...
	cout << "Q.20: Array length?" << endl;
	cout << " - sizeof entire array? " << sizeof(p_array1) << endl;
	cout << " - sizeof array element? " << sizeof(p_array1[0]) << endl;
	cout << " - array size n is: " << (sizeof(p_array1) / sizeof(p_array1[0])) << endl;
	// ##Q.20	Explain in your own words how the array size is calculated.
	// TIP: find out what the sizeof operator is. (It's not a function.)
	// ##Q.21-22 Go to the showParticleArray 2 implementation and see there ...
	cout << "Q.21 and Q.22: showParticleArray_2 differences ..." << endl;
	showParticleArray_2(p_array1, 3); // alternative signature

	// Tip: An easy array initialisation approach ... (note: it's not a 2-D array!)
	cout << "Tip: easy (~nested) initialisation ... " << endl;
	Particle p_array2[] = { {1,1,1}, {2,2,2}, {3,3,3} };
	showParticleArray(p_array2, 3); // works fine

	// Here we are going to read array positions that we haven't set properly.
	// ##Q.23	Change the size argument to 10 (or similar). What happens?
	// ##Q23.1	You might see some values that we set earlier. Why would this happen?
	cout << "Q.23: Array position overrun ... " << endl;
	showParticleArray(p_array2, 3); // <-- change size from 3 to 10
#endif

#if SECTION6
	// 6. Struct pointer with new and delete for memory
	cout << " << Section 6 >>" << endl;
	cout << "Q.24: Warm up concept checks ... " << endl;
	// ##Q24	Points to nothing - does it?
	Particle* p1_ptr; 
	cout << " - pointer address (does it?): " << hex << p1_ptr << endl;
	Particle p1 = { 9,9,9 }; // a real and initialised Particle variable
	cout << " - pointer address of p1:" << hex << &p1 << endl;
	p1_ptr = &p1; // copy the point to the same particle
	cout << " - pointer value of p1_ptr " << hex << p1_ptr << endl;
	// ##Q.25	What is "hex" and what does it do? (url in your notes)

	// Now lets create a Particle that we only access via a pointers
	cout << "Q.26 and Q.27: Using new and delete ... " << endl;
	p1_ptr = new Particle();
	// ##Q.26	What is new and what did it do?
	cout << " - pointer address " << hex << p1_ptr << endl;
	showParticle((*p1_ptr));
	cout << " - show via de-referenced pointer ... ";
	showParticle((*p1_ptr));
	cout << " - set a value via pointer" << endl;
	p1_ptr->age = 99;
	showParticle((*p1_ptr));
	// Clean up!
	delete p1_ptr;
	// ##Q.27	What is delete and what did it do?

	cout << "Q.28 Can we still show value at pointer address? (It was deleted, so ...) " << endl;
	cout << " - pointer address " << hex << p1_ptr << endl;
	// ##Q.28	What happens when we try this? Explain.
	showParticle((*p1_ptr));

	cout << "Q.29 nullptr vs NULL vs 0 ... for pointers." << endl;
	// house keeping - if a pointer isn't valid, set it to nullptr/NULL
	p1_ptr = nullptr; // You might see old/sample code with NULL or == 0
	cout << " - pointer address " << hex << p1_ptr << endl;
	if (p1_ptr == 0) { cout << " - Yes! p1_ptr == 0" << endl; }
	// ##Q.29	What is the difference between NULL and nullptr and 0?

	// ##Q.30	What happens in this line? (A zero address now, so ...)
	showParticle((*p1_ptr));
	// NOTE: There is a difference between "run" and "debug" in most IDEs
	// NOTE: If you do a simple run (not a debug) with the IDE, you should
	// normally get a "process finished with exit code 0" message at the end.
	// If the value given is NOT "0", the program stopped with an error code!
	// Make sure you know if this is the case. Run the program binary directly
	// from a terminal to confirm if there is an issue.
	// Debug will tell you *lot* more!
#endif

#if SECTION7
	// 7. Array of pointers to structs
	cout << " << Section 7 >>" << endl;
	const int n = 5;
	Particle* ptr_array[n]; // contains pointers to nowhere so far!
	cout << "Array of pointers - warmup checks:" << endl;
	cout << "The ptr_array value " << ptr_array << endl;
	cout << "Default ptr_array values " << endl;
	// default initial values
	for (int i = 0; i < n; i++) {
		cout << " - ptr_array[" << i << "] value " << hex << ptr_array[i] << endl;
	}
	// set each pointer to a safe default
	for (int i = 0; i < n; i++) {
		ptr_array[i] = nullptr;
	}
	// show the clean pointer values now ...
	cout << "Clean ptr_array values " << endl;
	for (int i = 0; i < n; i++) {
		cout << " - ptr_array[" << i << "] value " << hex << ptr_array[i] << endl;
	}
	// ##Q.31	Are default pointer values in an array safe? Explain.

	// Reserve memory for each particle and assign address
	// NOTE: These are just structs so think memory not constructor in this case.
	for (int i = 0; i < n; i++) {
		ptr_array[i] = new Particle();
		ptr_array[i]->age = i; // Note: Set the age so we can tell if it's working :)
	}
	// show each particle value
	cout << "Show each particle pointed to in the pointer array ..." << endl;
	for (int i = 0; i < n; i++) {
		cout << " - ";
		showParticle((*ptr_array[i]));
		// NOTE: we needed (*ptr_array[i]) to turn pointer into Particle parameter
	}
	// ##Q.32	We should always have "delete" to match each "new". What is the problem if we don't delete, and what is the common name for this?
	// ##Q.33	Your IDE may have tools to help you track memory. Does it?
	// ##Q.34	Can you see what happens if you DON'T do this?
	for (int i = 0; i < n; i++) {
		delete ptr_array[i];
		ptr_array[i] = nullptr;
		// ##Q.35	Should we set pointers to nullptr? Why?
	}

	// Note: if we dynamically created the array (with new), we should clean that up too.
	// ##Q.36	How do you create an array with new and set the size?
#endif

	return 0;
}

// Function details - each matches the function declarations at the top

void showParticle(Particle p)
{
	cout << "Particle: ";
	cout << "(age=" << p.age << "), ";
	cout << "(x,y)=(" << p.x << "," << p.y << ")" << endl;
}

Particle createParticleWith(int age, int x, int y)
{
	Particle result;
	result.age = age;
	result.x = x;
	result.y = y;
	return result;
}

void setParticleWith(Particle p, int age, int x, int y)
{
	p.age = age;
	p.x = x;
	p.y = y;
}

void showParticleArray(Particle* p_array, int size)
{
	// We can't ~actually~ pass an array, so ...
	// we pass a pointer to the first element of the array!
	// ... and the length. Which might be wrong.
	cout << "showParticleArray call ..." << endl;
	for (int i = 0; i < size; i++) {
		cout << " - pos=" << i << " ";
		showParticle(p_array[i]);
	}
}

void showParticleArray_2(Particle arr[], int size)
{
	// ##Q.21 What is the difference between this function signature and
	//  and the function signature for showParticleArray?
	cout << "showParticleArray_2 call ..." << endl;

	// ##Q.22 Uncomment the following. It gives different values to those we saw before
	//  So it won't work as a way to determine array size - but why?
	/*
	 if (true) {
		 cout << "Array as arr[] ..." << endl;
		 cout << " - sizeof entire array? " << sizeof(arr) << endl;
		 cout << " - sizeof array element? " << sizeof(arr) << endl;
		 cout << " - array size n is: " << (sizeof(arr) / sizeof(arr[0])) << endl;
	 }
	 */
	 // NOTE: The above might get warnings (good!). Not all compilers/IDEs though.
	 // Extra: Make a note about what is giving you warnings if you know.

	 // This is the same behaviour as original function
	for (int i = 0; i < size; i++) {
		cout << " - pos=" << i << " ";
		showParticle(arr[i]);
	}

	// Return to main for Q.23 ...
}