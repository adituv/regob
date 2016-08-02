#include <iostream>
#include <string>
#include <boost/program_options.hpp>

using namespace boost::program_options;
using namespace std;

void unpackGob(string, string, string);
void conflicting_options(const variables_map&, const char*, const char*);
void option_dependency(const variables_map&, const char*, const char*);

int main(int argc, const char* argv[]) {
	try {
		string gobpath;
		string headerpath;
		string outputpath = "./";

		options_description desc("Allowed options");
		desc.add_options()
			("help",                                              "print usage msesage")
			("version",                                           "print the program's name and version")
			("unpack,u", value(&gobpath),                         "unpack a GOB file")
			("header,h", value(&headerpath),                      "specify the header for the GOB file to unpack")
			("output,o", value(&outputpath)->default_value("./"), "specify the output directory of this command")
			;

		variables_map vm;
		store(parse_command_line(argc, argv, desc), vm);

		if (vm.count("help")) {
			cout << desc << endl;
			return 0;
		}

		if (vm.count("version")) {
			cout << "regob version 0.1.0.0" << endl;
			return 0;
		}

		option_dependency(vm, "unpack", "header");

		if (outputpath.back() != '/') outputpath.push_back('/');

		notify(vm);

		if (vm.count("unpack")) {
			unpackGob(gobpath, headerpath, outputpath);
		}
		else {
			throw logic_error("No operation specified.");
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	return 0;
}


// The following functions are taken from a boost.org example.
// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// See copy at http://www.boost.org/LICENSE_1_0.txt

/* Function used to check that 'opt1' and 'opt2' are not specified
at the same time. */
void conflicting_options(const variables_map& vm,
	const char* opt1, const char* opt2)
{
	if (vm.count(opt1) && !vm[opt1].defaulted()
		&& vm.count(opt2) && !vm[opt2].defaulted())
		throw logic_error(string("Conflicting options '")
			+ opt1 + "' and '" + opt2 + "'.");
}

/* Function used to check that of 'for_what' is specified, then
'required_option' is specified too. */
void option_dependency(const variables_map& vm,
	const char* for_what, const char* required_option)
{
	if (vm.count(for_what) && !vm[for_what].defaulted())
		if (vm.count(required_option) == 0 || vm[required_option].defaulted())
			throw logic_error(string("Option '") + for_what
				+ "' requires option '" + required_option + "'.");
}