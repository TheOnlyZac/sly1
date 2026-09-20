/**
 * @file splice/eval.h
 * Evaluation methods for Splice, which is semantically very close to Scheme.
 */
#ifndef SPLICE_EVAL_H
#define SPLICE_EVAL_H

#include "common.h"
#include <splice/ref.h>

// Forward declarations.
class CPair;
class CFrame;

/**
 * Evaluates a symbol by looking up its ID in the frame structure.
 *
 * @param ppair Lisp pair containing a symbol in its first slot.
 * @param pframe Context frame.
 * @return The value of the evaluated symbol.
 */
CRef RefEvalSymbol(CPair *ppair, CFrame *pframe);

/**
 * Evaluates a "set" statement, assigning a new value to an existing variable.
 *
 * (set <variable> <expression>)
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return TODO: whatever is returned by CFrame::RefSetBinding()
 */
CRef RefEvalSet(CPair *ppair, CFrame *pframe);

/**
 * Evaluates a "define" statement, declaring a new variable with its value.
 *
 * (define <variable> <expression>)
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return TODO: whatever is returned by CFrame::RefAddBinding()
 */
CRef RefEvalDefine(CPair *ppair, CFrame *pframe);

/**
 * Evaluates an "assert" statement, printing to the debug console if it fails,
 * along with the "description" field.
 *
 * (assert <expression> {description})
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Void reference.
 */
CRef RefEvalAssert(CPair *ppair, CFrame *pframe);

/**
 * Evaluates an "if" statement, which conditionally executes a body and optional else
 * statement depending on the value of its input.
 *
 * (if <expression> <true-stmt> {else-stmt})
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return The return of whatever branch was taken, or void reference if none executed.
 */
CRef RefEvalIf(CPair *ppair, CFrame *pframe);

/**
 * Evaluates an "or" expression, which returns true if any of its variadic arguments are true.
 * Will short circuit at the first truthy expression.
 *
 * (or <expr1> ...)
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Truthy value of the last evaluated expression, or explicit false reference.
 */
CRef RefEvalOr(CPair *ppair, CFrame *pframe);

/**
 * Evaluates an "and" expression, which returns true if all of its variadic arguments are true.
 * Will short circuit at the first false expression.
 *
 * (and <expr1> ...)
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Truthy value of the last evaluated expression, or explicit false reference.
 */
CRef RefEvalAnd(CPair *ppair, CFrame *pframe);

/**
 * Evaluates a "cond" expression, which searches through a list of conditional statements and
 * evaluates and returns the first one that evaluates to true.
 *
 *  (cond
 *   {(<test-expr-1> <body-stmt-1> ...)}
 *   {(<test-expr-2> <body-stmt-2> ...)}
 *   {(else <else-stmt-1> ...})
 * )
 * Each sublist is traversed in order and its expression is evaluated.
 * If it evaluates truthy, then the body expression(s) are evaluated and returned.
 * If no expression evaluates truthy, then the first "else" statement is evaluated and returned.
 * If no else statements exist, then the return type is a Void reference.
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Matched expression.
 */
CRef RefEvalCond(CPair *ppair, CFrame *pframe);

/**
 * Evaluates a "case" expression, which searches through a list of statements, each with a
 * list of potential values and evaluates and returns the first one that matches.
 *
 *  (case <value>
 *   {((<datum-1 ...>) <body-stmt-1> ...)}
 *   {((<datum-2 ...>) <body-stmt-2> ...)}
 *   {(else <default-stmt-1> ...)}
 * )
 * )
 * Each sublist is traversed in order and its datum list matched against "value".
 * If it evaluates truthy, then the body expression(s) are evaluated and returned.
 * If no expression evaluates truthy, then the first "else" statement is evaluated and returned.
 * If no else statements exist, then the return type is a Void reference.
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Matched expression.
 */
CRef RefEvalCase(CPair *ppair, CFrame *pframe);

/**
 * Evaluates a "let" expression, which defines variables for a scoped body expression.
 *
 *  (let (
 *    (<var-1> <expr-1>)
 *    (<var-2> <expr-2>)
 *    ...)
 *    body-expr-1...
  * )
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Evaluation of the body expression(s).
 */
CRef RefEvalLet(CPair *ppair, CFrame *pframe);

/**
 * Evaluates a "while" expression: the body continues to execute while the conditional is truthy.
 *
 * (while <cond-expr> <body-stmt>)
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Void reference.
 */
CRef RefEvalWhile(CPair *ppair, CFrame *pframe);

/**
 * Creates an anonymous lambda function.
 *
 * (lambda (<param-1> <param-2> ...) <body-stmt>)
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Reference to the newly created lambda.
 */
CRef RefEvalLambda(CPair *ppair, CFrame *pframe);

/**
 * Evaluates each body statment of a lambda function.  This is used by RefEvalApply().
 *
 * @param ppair Lisp pair containing the lambda body.
 * @param pframe Context frame.
 * @return Return value of the last executed body statement.
 */
CRef RefEvalLambdaBody(CPair *ppair, CFrame *pframe);

/**
 * Evaluates a "begin" statement, which simply executes several child statements and returns the
 * value of the last one.
 *
 * (begin <statement-1> ...)
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Evaluation of the last statement.
 */
CRef RefEvalBegin(CPair *ppair, CFrame *pframe);

/**
 * Calls a function.  The last argument may be an (optional) variadic list of arguments that
 * is unpacked and passed to the target function.
 *
 * (apply <function> <arg-expr-1> ... {list})
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Return value of the evaluated function.
 */
CRef RefEvalApply(CPair *ppair, CFrame *pframe);

/**
 * Imports a module, exact semantics unknown.
 *
 * (import <module?>)
 *
 * @param ppair Lisp pair whose first entry contains a list of the arguments.
 * @param pframe Context frame.
 * @return Void reference;
 */
CRef RefEvalImport(CPair *ppair, CFrame *pframe);

/**
 * Generically evaluates a pair, dispatching to one of the above routines.
 *
 * @param ppair Lisp pair to evaluate.
 * @param pframe Context frame.
 * @return Return reference of the evaluation.
 */
CRef RefEval(CPair *ppair, CFrame *pframe);

#endif // SPLICE_EVAL_H
