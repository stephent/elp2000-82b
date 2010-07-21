/*
 * series.h
 * Created by Serhii Tsyba (sertsy@gmail.com) on 08.06.10.
 *
 * This file contains routines to compute series of the ELP theory. There are four series in total and a seperate
 * function is given for each of the serie. Expressions for series are
 *
 *              A{sin|cos}(i₁D + i₂l' + i₃l + i₄F)
 *              Asin(i₁ζ + i₂D + i₃l' + i₄l + i₅F + φ)
 *              Asin(i₁Me + i₂V + i₃T + i₄Ma + i₅J + i₆S + i₇U + i₈N + i₉D + i₁₀l + i₁₁F + φ)
 *              Asin(i₁Me + i₂V + i₃T + i₄Ma + i₅J + i₆S + i₇U + i₈D + i₉l + i₁₀l' + i₁₁F + φ)
 *
 * First serie uses either sine when computing longitude and latitude and cosine when computing radial distance. For
 * the sake of code simplicity two separate functions are given for either expressions.
 *
 * Each function takes different set of arguments each is explained in more detail for every function in its own
 * commentary. It should be noted that indexing of all arrays of the argumets should be preserved as stated in the
 * description.
 *
 * Output value of every function is measured in arcseconds.
 */

#ifndef SERIES_H
#define SERIES_H

#define ARCSECONDS_IN_DEGREE 3600.0         // definition for converting arcseconds to radians

/*
 * Converts given amount of degrees into radians.
 */
double radian(double d);

/*
 * Computes a sine Fourier serie for the Main Problem
 *
 *                                      Σ Asin(i₁D + i₂l' + i₃l + i₄F)
 *
 * where Delaunay arguments D, l', l, F are given as a first argument and multipliers iᵢ are given as a second
 * argument. Indices of the Delaunay arguments array and each row of multipliers array must match.
 * Coefficients Aᵢ are given as a first column of the coefficients array. Other six columns hold derivatives of A:
 * ∂A/∂σᵢ and are given that way to preserve data structures of the ELP theory.
 * Last argument specifies the size of a serie, i.e. size of the arrays multipliers and coefficients.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 2
 */
double compute_serie_a_sin(double delaunay_arguments[], int multipliers[][4], double coefficients[][7], int n);

/*
 * Computes a cosine Fourier serie for the Main Problem
 *
 *                                      Σ Acos(i₁D + i₂l' + i₃l + i₄F)
 *
 * where Delaunay arguments D, l', l, F are given as a first argument and multipliers iᵢ are given as a second
 * argument. Indices of the Delaunay arguments array and each row of multipliers array must match.
 * Coefficients Aᵢ are given as a first column of the coefficients array. Other six columns hold derivatives of A:
 * ∂A/∂σᵢ and are given that way to preserve data structures of the ELP theory.
 * Last argument specifies the size of a serie, i.e. size of the arrays multipliers and coefficients.
 * Differentiation for sine and cosine series is done for code simplicicty.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 2
 */
double compute_serie_a_cos(double delaunay_arguments[], int multipliers[][4], double coefficients[][7], int n);

/*
 * Computes a Fourier serie for Earth figure perturbations, tidal effects, Moon figure perturbations, relativistic
 * perturbations and second order planetary perturbations given the expression
 *
 *                              Σ Asin(i₁ζ + i₂D + i₃l' + i₄l + i₅F + φ)
 *
 * where indices i are given in each row of multipliers array, precession value ζ is given as a first adrgument,
 * Delaunay arguments D, l, l', F are given as a second parameter. Each row of coefficients gives φ, A, P, where P is
 * an approximate period value and not used in the computation, but preserved for consistency of the ELP theory data
 * structures. Last argument specifies the size of a serie, i.e. size of the arrays multipliers and coefficients.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 2
 */
double compute_serie_b(double precession, double delaunay_arguments[], int multipliers[][5], double coefficients[][3], int n);

/*
 * Computes first type Fourier series for planetary perturbations (constant and linear), which does not include
 * summation of l' Delaunay argument.
 * Given the epression
 *
 *              Σ Asin(i₁Me + i₂V + i₃T + i₄Ma + i₅J + i₆S + i₇U + i₈N + i₉D + i₁₀l + i₁₁F + φ)
 *
 * where 11 indices i are stored in each row of multipliers array. Planetary constants Me (Mercury), V (Venus),
 * T (Earth), Ma (Mars), J (Jupiter), S (Saturn), U (Uranus) and N (Neptune) are given as a first argument and all
 * four Delaunay arguments are given as a second argument preserving mentioned indices.
 * Each row of coefficients array gives φ, A, P, where P is an approximate period value and not used in the
 * computation, but preserved for consistency of the ELP theory data structures.
 * Last argument specifies the size of a serie, i.e. size of the arrays multipliers and coefficients. 
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 3
 */
double compute_serie_c(double planetary_arguments[], double delaunay_arguments[], int multipliers[][11], double coefficients[][3], int n);

/*
 * Computes second type Fourier series for planetary perturbations (constant and linear), which does not include
 * summation of planetary argument of Neptune.
 * Given the epression
 *
 *              Σ Asin(i₁Me + i₂V + i₃T + i₄Ma + i₅J + i₆S + i₇U + i₈D + i₉l + i₁₀l' + i₁₁F + φ)
 *
 * where 11 indices i are stored in each row of multipliers array. Planetary constants Me (Mercury), V (Venus),
 * T (Earth), Ma (Mars), J (Jupiter), S (Saturn) and U (Uranus) are given as a first argument and Delaunay
 * arguments are given as a second argument preserving mentioned indices.
 * Each row of coefficients array gives φ, A, P, where P is an approximate period value and not used in the
 * computation, but preserved for consistency of the ELP theory data structures.
 * Last argument specifies the size of a serie, i.e. size of the arrays multipliers and coefficients. 
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 3
 */
double compute_serie_d(double planetary_arguments[], double delaunay_arguments[], int multipliers[][11], double coefficients[][3], int n);

#endif // SERIES_H