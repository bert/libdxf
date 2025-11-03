# Contributing to libDXF.

## How to contribute.

Your patches, issues, ideas and bug reports are essential for getting libDXF
better and achieving a great library of DXF routines and tools.
We simply can't access the huge number of platforms and myriad configurations
for running libDXF.
We want to keep it as easy as possible to contribute changes that get things
working in your environment.
There are a few guidelines that we need contributors to follow so that we can
have a chance of keeping on top of things.


## Getting Started.

On Github:
* Make sure you have a GitHub account.
* Submit a ticket for your issue, assuming one does not already exist.
* Clearly describe the issue including steps to reproduce when it is a bug.
* Make sure you mention the earliest version that you know has the issue.
* Fork the repository on GitHub if you are going to create a patch, and
  do a "pull request", this is best done on a separate topic branch.

Or on Launchpad:
* Make sure you have a Launchpad account.
* Sign the Code of Conduct.
* Submit a bug report for your issue, assuming one does not already exist.
* Clearly describe the issue including steps to reproduce when it is a bug.
* Make sure you mention the earliest version that you know has the issue.


## Making Changes.

* Create a topic branch from where you want to base your work, this is
  usually not the master branch.
* Only target release branches if you are certain your fix must be on
  that branch.
* To quickly create a topic branch based on master with:
    git branch fix/master/my_contribution master
* Checkout the new branch with:
    git checkout fix/master/my_contribution
* Or do this combined with:
    git checkout -b fix/master/my_contribution
* Make commits of logical units.
* Check for unnecessary whitespace with git diff --check before committing.
* Make sure your commit messages are in the proper format:
    (#99999) Make the example in CONTRIBUTING imperative and concrete

    Without this patch applied the example commit message in the CONTRIBUTING
    document is not a concrete example.  This is a problem because the
    contributor is left to imagine what the commit message should look like
    based on a description rather than an example.  This patch fixes the
    problem by making the example concrete and imperative.

* The first line is a real life imperative statement with a ticket number
  from our issue tracker.
* The body describes the behavior without the patch,
  why this is a problem, and how the patch fixes the problem when applied.
* Make sure you have added the necessary tests for your changes.
* Run all the tests to assure nothing else was accidentally broken.


## Submitting Changes.

On Github:
* Push your changes to a topic branch in your fork of the repository.
* Submit a pull request to the repository in the libDXF organization.

Or on Launchpad:
* Sign the Code of Conduct, if you haven't done that yet.
* Update your Launchpad bug report to mark that you have submitted code and are
  ready for it to be reviewed.
* Include a link to the pull request or topic branch in the bug report.


## Cooperative Principle.

"Make your contribution such as it is required, at the stage at which it occurs,
by the accepted purpose or direction of the talk exchange in which you are
engaged." (Grice, H.P. (1989), Studies in the Way of Words, Harvard University
Press).

The conversational maxims can be thought of as precisifications of the
cooperative principle that deal specifically with communication.
These apply to computer linguistics and thus source code as well.

Maxim of Quantity: Information
* Make your contribution as informative as is required for the current
  purposes of the exchange.
* Do not make your contribution more informative than is required.

Maxim of Quality: Truth
* Do not say what you believe to be false.
* Do not say that for which you lack adequate evidence.

Maxim of Relation: Relevance
* Be relevant.

Maxim of Manner: Clarity ("be perspicuous")
* Avoid obscurity of expression.
* Avoid ambiguity.
* Be brief (avoid unnecessary prolixity).
* Be orderly.


## Rationale on Coding Style.

Here follow some notes to myself, or any other volunteer contributor who
wants to join the effort.
The coding style I follow is the Allman style, named after Eric Allman.
It is sometimes referred to as "ANSI style" for its use in the documents
describing the ANSI C standard.
Proponents of this style often cite its use by ANSI and in other
standards as justification for its adoption.
This style is similar to the standard indentation used by the Pascal
programming language and Transact-SQL, where the braces are equivalent to the
"begin" and "end" keywords.
As I started programming in Pascal way back in the 80's of the former century, 
this is the reason for using this coding style in my C code.
If you choose to join in on the fun with your own style, this is not a show
stopper for me.
Please understand that I might reformat your contribution to my own likings as
not to strain my eyes too much.


## File headers.

File headers contain Doxygen style tags for doumentation generated with Doxygen.
A default header looks similar to the following:

```
/*!
 * \file default.c
 *
 * \author Copyright (C) 2008 by Author <author@email.address>
 *
 * \brief A brief description of the files use.
 *
 * \version Stating conformance with the DXF released version mentioned.
 *
 * A more elaborate description follows here, and can span several lines.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.\n
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n
 * See the GNU General Public License for more details.\n
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to:\n
 * the Free Software Foundation, Inc., \n
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
```

## C-header files.
The following is taken from "Libtool", "Shared library support for GNU",
section 8.1 "Writing C header files", to be found here:
<http://www.gnu.org/software/libtool/manual/html_node/index.html>.
 
Writing portable C header files can be difficult, since they may be read by
different types of compilers:

### C++ compilers

C++ compilers require that functions be declared with full prototypes, since
C++ is more strongly typed than C. C functions and variables also need to be
declared with the extern "C" directive, so that the names aren’t mangled.
See C++ libraries, for other issues relevant to using C++ with libtool.

### ANSI C compilers

ANSI C compilers are not as strict as C++ compilers, but functions should be
prototyped to avoid unnecessary warnings when the header file is #included.

### non-ANSI C compilers

Non-ANSI compilers will report errors if functions are prototyped. 

These complications mean that your library interface headers must use some C
preprocessor magic to be usable by each of the above compilers.

foo.h in the tests/demo subdirectory of the libtool distribution serves as an
example for how to write a header file that can be safely installed in a system
directory.

Here are the relevant portions of that file:

```
    /* BEGIN_C_DECLS should be used at the beginning of your declarations,
       so that C++ compilers don't mangle their names.  Use END_C_DECLS at
       the end of C declarations. */
    #undef BEGIN_C_DECLS
    #undef END_C_DECLS
    #ifdef __cplusplus
    # define BEGIN_C_DECLS extern "C" {
    # define END_C_DECLS }
    #else
    # define BEGIN_C_DECLS /* empty */
    # define END_C_DECLS /* empty */
    #endif

    /* PARAMS is a macro used to wrap function prototypes, so that
       compilers that don't understand ANSI C prototypes still work,
       and ANSI C compilers can issue warnings about type mismatches. */
    #undef PARAMS
    #if defined __STDC__ || defined _AIX \
            || (defined __mips && defined _SYSTYPE_SVR4) \
            || defined WIN32 || defined __cplusplus
    # define PARAMS(protos) protos
    #else
    # define PARAMS(protos) ()
    #endif
```

These macros are used in foo.h as follows:

```
#ifndef FOO_H
#define FOO_H 1

/* The above macro definitions. */
#include "…"

BEGIN_C_DECLS

int foo PARAMS((void));
int hello PARAMS((void));

END_C_DECLS

#endif /* !FOO_H */
```

Note that the #ifndef FOO_H prevents the body of foo.h from being read more than
once in a given compilation (see the following paragraph "Header guards").

Also the only thing that must go outside the BEGIN_C_DECLS/END_C_DECLS pair are
#include lines.
Strictly speaking it is only C symbol names that need to be protected, but your
header files will be more maintainable if you have a single pair of these macros
around the majority of the header contents.

You should use these definitions of PARAMS, BEGIN_C_DECLS, and END_C_DECLS into
your own headers.
Then, you may use them to create header files that are valid for C++, ANSI, and
non-ANSI compilers.

For a non-glib way choose:

```
#ifdef __cplusplus
extern "C" {
#endif

void foo (int i);

#ifdef __cplusplus
}
#endif
```

## Portability

Do not be naive about writing portable code.
Following the tips given above will help you miss the most obvious problems, but
there are definitely other subtle portability issues.
You may need to cope with some of the following issues:

- Pre-ANSI compilers do not always support the void * generic pointer type,
  and so need to use char * in its place.
- The const, inline and signed keywords are not supported by some compilers,
  especially pre-ANSI compilers.
- The long double type is not supported by many compilers.

## Header guards.

All header files should have #define guards to prevent multiple inclusion.
The format of the symbol name should be <PROJECT>_<PATH>_<FILE>_H_.

To guarantee uniqueness, they should be based on the full path in the project's
source tree.
For example, the file foo/src/bar/baz.h in project foo should have the following
guard:

```
#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_

...

#endif /* FOO_BAR_BAZ_H_ */
```

## Doxygen style comments.

The prefered style for a Doxygen comment for a function or any other entity is:

```
/*!
 * \brief Brief description.
 *
 * Followed by a more verbose description of what is to be explained about the 
 * entity.
 *
 * \param Description of a parameter.
 *
 * \return Return value can be described here.
 *
 * \bugs Can be reported here.
 *
 * \exception Can be described here.
 *
 * \since To describe in which version this feature was implemented.
 *
 * \deprecated To describe in which version this feature was deprecated.
 *
 * \version Describe compliance with version of DXF.
 *
 * \todo Can be described here.
 *
 * The more verbose Doxygen comment is closed with:
 */
``` 

## Comments.

```
/* Comments should be added at the correct level of identation. */

/* More elaborate comments, which span across the 80 character limit,
 * (described below) should have an asterisk in front on every line of the
 * comment.
 */
```

## Indentation.

To contribute to this code you need to set emacs (or whatever editor you use) to
8 indentation steps and {} at the right places (see code).
No tabs, just plain spaces, except in Makefiles and config stuff where tabs 
have a meaning.

My ~/.emacs are:

```lisp
(defun my-c-mode-hook ()
  (turn-on-font-lock)
  (setq c-basic-offset 8))

(add-hook 'c-mode-hook 'my-c-mode-hook)
```

## Truncation.

It is prefered for lines to not extend beyond 80 characters long.
If you continue the line of code at the following line please add 2 spaces to
the current ident level.
If you need more than 40 characters to ident (5 levels) you probably should 
write a function.
However, I'm not very strict about this myself.
Please do truncate a line at a convenient position, for example:

```
        if (((very_elaborate_variable_description_1 > 0)
          || (very_elaborate_variable_description_2 < 0))
          && (very_elaborate_variable_description_3 > 1000))
        {
                blah;
        }
```

Improve readability by putting the operator at the start of the new line.


## Curly Braces.

```
if () 
{
        blah1 ();
        blah2 ();
} 
else
{
        yada1 ();
        yada2 ();
}
```

If there is only one statement you don't need the braces.

```
for () 
{
        do_whatever1 ();
        do_whatever2 ();
}

switch ()
{
        case foo:
                blah1 ();
                break;
        case bar:
                blah2 ();
                break;
        default:
                break;
}
```

Switch should always have a default case.
Note the whitespace before the ().


## ChangeLog.

A ChangeLog is generated from all commit message entries entered when a blob
of code is committed with git.
Generate the ChangeLog prior to a new release.


## About git commit messages and blobs.

Keep commit messages as clear as possible:

If a file is added or deleted mentioning "new file: blah.c" or 
"deleted file: blah2.c" says it all.

Keep blobs as granular as possible, do not commit blobs from different files in 
a single commit. I would rather have five commits if that is what it takes.


## About git branches and merging.

Use the branch and merge functionality of git for every experiment or issue
[#ticket] to be solved.
As I'm still learning things about git every day I find this a good practice,
and I'm going to have to adopt to this myself.


## Functions.

The prototype should have return type on the same line as function name:
int some_function (int par1, int par2);

The function implementation should have return type on a separate line
(including eventual pointer star).
The function implementation should have the function name in c-comments
at the closing brace, although I'm not strict with doing this myself (me bad).

```
int *
some_function (int par1, int par2)
{
        /* Implementation */
} /* some_function */
```

or 

```
int *
some_function
(
        int par1, /*!< some Doxygen comment about par1 */
        int par2
                /*!< some Doxygen comment about par2 which is more elaborate 
                 * and extends the 80 character limit by far.\n
                 * Add a \n when a new line is to be generated in the Doxygen 
                 * documentation. 
                 */
)
{
        /* Implementation */
} /* some_function */
```

In a function there should be a maximum of one empty line in a row.
Between functions there should be two empty lines.


## Log messages.

It is prefered to log error messages similar like the following example:
```
  fprintf (stderr,
    (_("Error in %s () could not allocate memory.\n")),
     __FUNCTION__);
```


## 0, 0.0, NULL and '\0'.

Use 0 for integers, 0.0 for reals, NULL for pointers, and '\0' for chars.

Use 0 for integers and 0.0 for reals. This is not controversial.

For pointers (address values), there is a choice between 0, NULL, and nullptr.
We prefer NULL because it looks like a pointer.
In fact, some C compilers provide special definitions of NULL which enable them
to give useful warnings, particularly in situations where sizeof(NULL) is not
equal to sizeof(0).

Use '\0' for chars. This is the correct type and also makes code more readable.


## sizeof().

Prefer sizeof(varname) to sizeof(type).

Use sizeof(varname) when you take the size of a particular variable.
sizeof(varname) will update appropriately if someone changes the variable type
either now or later.
You may use sizeof(type) for code unrelated to any particular variable, such as
code that manages an external or internal data format where a variable of an
appropriate C type is not convenient.


## End Of File

The End Of File is denoted with a comment and a blank line such as:

/* EOF */

