// SPDX-License-Identifier: GPL-3.0-or-later
/**
 * Source Annotation Language
 */
// Created by Romain on 05/05/2021.

#ifndef ROMAINOS_SAL_H
#define ROMAINOS_SAL_H

/**
 * Variable d'entrée
 */
#define _In_

/**
 * Variable d'entrée facultative, peut valoir nullptr
 */
#define _In_opt_

/**
 * Variable entrée / sortie
 */
#define _Inout_

/**
 * Variable entrée / sortie facultative, peut valoir nullptr
 */
#define _Inout_opt_

/**
 * Variable de sortie, pointeur
 */
#define _Out_

/**
 * Variable de sortie facultative, peut valoir nullptr
 */
#define _Out_opt_

/**
 * Variable vers variable de sortie, double pointeur, ne peut valoir nullptr.
 */
#define _Deref_out_

/**
 * Variable vers variable de sortie, double pointeur, peut valoir nullptr.
 *
 * Ex: <code>
 * _Deref_out_opt_ int **pInt
 * int *pInt2 = new int;
 * *pInt2 = 6;
 * if(pInt != NULL)
 *     *pInt = pInt2;
 * </code>
 */
#define _Deref_out_opt_

/**
 * Valeur de retour
 */
#define _Ret_

/**
 * Valeur de retour double pointeur
 */
#define _Deref_ret_

/**
 * Nullable
 */
#define _Nullable
#define __nullable _Nullable

/**
 * Non null
 */
#define _Nonnull
#define __nonnull _Nonnull

#endif //ROMAINOS_SAL_H
