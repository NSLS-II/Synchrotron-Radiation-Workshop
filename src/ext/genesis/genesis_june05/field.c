/* field.f -- translated by f2c (version 20000118).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

Extern struct {
    //doublecomplex crfield[29241], crsource[29241], crmatc[171], cstep, crhm[29241], cwet[171], cbet[171];
	doublecomplex *crfield, *crsource, crmatc[513], cstep, *crhm, cwet[513], cbet[513];
    doublereal dxy, xks, radphase;
} cartcom_;

#define cartcom_1 cartcom_

Extern struct {
    doublereal aw0, xkx, xky, wcoefz[3], xlamd, fbess0, delaw, awd, awx, awy, 
	    gamma0, delgam, rxbeam, rybeam, alphax, alphay, emitx, emity, 
	    xbeam, ybeam, pxbeam, pybeam, cuttail, curpeak, conditx, condity, 
	    bunch, bunchphase, emod, emodphase, xlamds, prad0, zrayl, zwaist, 
	    rmax0, zsep, delz, zstop, quadf, quadd, fl, dl, drl, f1st, qfdx, 
	    qfdy, sl, solen, curlen, shotnoise, svar, dgrid, eloss, version, 
	    ibfield, imagl, idril;
    integer iseed, nwig, nsec, npart, ncar, lbc, nscr, nscz, nptr, ildgam, 
	    ildpsi, ildx, ildy, ildpx, ildpy, itgaus, nbins, iphsty, ishsty, 
	    ippart, ispart, ipradi, isradi, iertyp, iwityp, idump, iotail, 
	    nharm, magin, magout, lout[35], ffspec, ntail, nslice, iall, itdp,
	     ipseed, iscan, nscan, isntyp, isravg, isrsig, iorb, ndcut, 
	    idmppar, idmpfld, ilog, igamgaus, convharm, alignradf, offsetradf,
	     multconv;
    char beamfile[30], fieldfile[30], maginfile[30], magoutfile[30], 
	    outputfile[30], inputfile[30], scan[30], distfile[30], partfile[
	    30], filetype[30], radfile[30];
} inputcom_;

#define inputcom_1 inputcom_

Extern struct {
    //doublecomplex crwork3[116964], cpart1[70001], cpart2[70001];
    //doublereal k2gg[70001], k2pp[70001], k3gg[70001], k3pp[70001], p1[70001], 
	   // p2[70001];
	doublecomplex *crwork3, *cpart1, *cpart2;
	doublereal *k2gg, *k2pp, *k3gg, *k3pp, *p1, *p2;
} workspace_;

#define workspace_1 workspace_

/* Table of constant values */

static doublecomplex c_b5 = {1.,0.};

/* Subroutine */ int field_()
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5, i__6, i__7, i__8, i__9, i__10;
    doublecomplex z__1, z__2, z__3, z__4, z__5, z__6;

    /* Local variables */
    static integer ix, idx;
    extern /* Subroutine */ int tridagx_(), tridagy_();

/*     ================================================================== */
/*     integrate the wave equation one step in z for cartesian mesh */
/*     using adi - methode (alternationg direction implicit) */
/*        1: u(n+1/2)=u(n)+alpha/2(dx u(n+1/2)+dy u(n)) */
/*        2: u(n+1)=u(n+1/2)+alpha/2(dx u(n+1/2)+dy u(n+1)) */
/*        to use tridiag methode transpose data array: */
/*        (1)->u(n)->u(i,j)->u(j,i)->u(n)->(2)->transpose again */
/*     ------------------------------------------------------------------ */





/*     error codes */

/* genesis version */
/* platform */
/* indicator for original fil */
/* indicator for sdds filetyp */
/* # of particles */
/* # of integration steps */
/* # of slices */
/* maximum of harmonics */
/* maximum of particle i */
/* <> 0 keeps distribution in */
/* energy units (mc^2) in ev */
/* vacuum impedence in ohms */
/* speed of light * electron */
/* pi */
/* pi/2 */
/* 2*pi */
/* check i for precission */
/* check ii for precission */
/* number of radial points fo */
/* # of gridpoints of cartesi */


/*     function prototypes */

/*     -------------------------------------------------------------------- */
/*     cartesian mesh */




/*     ------------------------------------------------------ */
/*     all input variables */

/*     wiggler */
/*     electron beam */
/*     radiation */
/*     grid-quantities */
/*     control */
/*     strong focusing */
/*     loading */
/*     output */
/*     external files */
/*     time-dependency */
/*     scan */
/*     extension */



/*     homogenious part to right hand side of diff equation (1) */
/*     ------------------------------------------------------------------ */

    i__1 = inputcom_1.ncar;
    for (ix = 1; ix <= i__1; ++ix) {
	i__2 = ix - 1;
	i__3 = ix - 1;
	i__4 = ix - 1;
	z__2.r = cartcom_1.crsource[i__3].r + cartcom_1.crfield[i__4].r, 
		z__2.i = cartcom_1.crsource[i__3].i + cartcom_1.crfield[i__4]
		.i;
	i__5 = ix + inputcom_1.ncar - 1;
	i__6 = ix - 1;
	z__5.r = cartcom_1.crfield[i__5].r - cartcom_1.crfield[i__6].r, 
		z__5.i = cartcom_1.crfield[i__5].i - cartcom_1.crfield[i__6]
		.i;
	i__7 = ix - 1;
	z__4.r = z__5.r - cartcom_1.crfield[i__7].r, z__4.i = z__5.i - 
		cartcom_1.crfield[i__7].i;
	z__3.r = cartcom_1.cstep.r * z__4.r - cartcom_1.cstep.i * z__4.i, 
		z__3.i = cartcom_1.cstep.r * z__4.i + cartcom_1.cstep.i * 
		z__4.r;
	z__1.r = z__2.r + z__3.r, z__1.i = z__2.i + z__3.i;
	cartcom_1.crhm[i__2].r = z__1.r, cartcom_1.crhm[i__2].i = z__1.i;
    }
    i__1 = inputcom_1.ncar * (inputcom_1.ncar - 1);
    for (idx = inputcom_1.ncar + 1; idx <= i__1; ++idx) {
	i__2 = idx - 1;
	i__3 = idx - 1;
	i__4 = idx - 1;
	z__2.r = cartcom_1.crsource[i__3].r + cartcom_1.crfield[i__4].r, 
		z__2.i = cartcom_1.crsource[i__3].i + cartcom_1.crfield[i__4]
		.i;
	i__5 = idx + inputcom_1.ncar - 1;
	i__6 = idx - inputcom_1.ncar - 1;
	z__6.r = cartcom_1.crfield[i__5].r + cartcom_1.crfield[i__6].r, 
		z__6.i = cartcom_1.crfield[i__5].i + cartcom_1.crfield[i__6]
		.i;
	i__7 = idx - 1;
	z__5.r = z__6.r - cartcom_1.crfield[i__7].r, z__5.i = z__6.i - 
		cartcom_1.crfield[i__7].i;
	i__8 = idx - 1;
	z__4.r = z__5.r - cartcom_1.crfield[i__8].r, z__4.i = z__5.i - 
		cartcom_1.crfield[i__8].i;
	z__3.r = cartcom_1.cstep.r * z__4.r - cartcom_1.cstep.i * z__4.i, 
		z__3.i = cartcom_1.cstep.r * z__4.i + cartcom_1.cstep.i * 
		z__4.r;
	z__1.r = z__2.r + z__3.r, z__1.i = z__2.i + z__3.i;
	cartcom_1.crhm[i__2].r = z__1.r, cartcom_1.crhm[i__2].i = z__1.i;
    }
    i__1 = inputcom_1.ncar * inputcom_1.ncar;
    for (idx = inputcom_1.ncar * (inputcom_1.ncar - 1) + 1; idx <= i__1; 
	    ++idx) {
	i__2 = idx - 1;
	i__3 = idx - 1;
	i__4 = idx - 1;
	z__2.r = cartcom_1.crsource[i__3].r + cartcom_1.crfield[i__4].r, 
		z__2.i = cartcom_1.crsource[i__3].i + cartcom_1.crfield[i__4]
		.i;
	i__5 = idx - inputcom_1.ncar - 1;
	i__6 = idx - 1;
	z__5.r = cartcom_1.crfield[i__5].r - cartcom_1.crfield[i__6].r, 
		z__5.i = cartcom_1.crfield[i__5].i - cartcom_1.crfield[i__6]
		.i;
	i__7 = idx - 1;
	z__4.r = z__5.r - cartcom_1.crfield[i__7].r, z__4.i = z__5.i - 
		cartcom_1.crfield[i__7].i;
	z__3.r = cartcom_1.cstep.r * z__4.r - cartcom_1.cstep.i * z__4.i, 
		z__3.i = cartcom_1.cstep.r * z__4.i + cartcom_1.cstep.i * 
		z__4.r;
	z__1.r = z__2.r + z__3.r, z__1.i = z__2.i + z__3.i;
	cartcom_1.crhm[i__2].r = z__1.r, cartcom_1.crhm[i__2].i = z__1.i;
    }

/*     neumann boundary condition */
/*     ------------------------------------------------------------------ */

    if (inputcom_1.lbc != 0) {
	idx = inputcom_1.ncar * (inputcom_1.ncar - 1);
	i__1 = inputcom_1.ncar;
	for (ix = 1; ix <= i__1; ++ix) {
	    i__2 = ix - 1;
	    i__3 = ix - 1;
	    i__4 = ix + inputcom_1.ncar - 1;
	    z__2.r = cartcom_1.cstep.r * cartcom_1.crfield[i__4].r - 
		    cartcom_1.cstep.i * cartcom_1.crfield[i__4].i, z__2.i = 
		    cartcom_1.cstep.r * cartcom_1.crfield[i__4].i + 
		    cartcom_1.cstep.i * cartcom_1.crfield[i__4].r;
	    z__1.r = cartcom_1.crhm[i__3].r + z__2.r, z__1.i = cartcom_1.crhm[
		    i__3].i + z__2.i;
	    cartcom_1.crhm[i__2].r = z__1.r, cartcom_1.crhm[i__2].i = z__1.i;
	    i__2 = idx + ix - 1;
	    i__3 = idx + ix - 1;
	    i__4 = idx + ix - inputcom_1.ncar - 1;
	    z__2.r = cartcom_1.cstep.r * cartcom_1.crfield[i__4].r - 
		    cartcom_1.cstep.i * cartcom_1.crfield[i__4].i, z__2.i = 
		    cartcom_1.cstep.r * cartcom_1.crfield[i__4].i + 
		    cartcom_1.cstep.i * cartcom_1.crfield[i__4].r;
	    z__1.r = cartcom_1.crhm[i__3].r + z__2.r, z__1.i = cartcom_1.crhm[
		    i__3].i + z__2.i;
	    cartcom_1.crhm[i__2].r = z__1.r, cartcom_1.crhm[i__2].i = z__1.i;
	}
    }

/*     solve the tridiagonal system 1 */
/*     ------------------------------------------------------------------ */

    tridagx_(cartcom_1.crmatc, cartcom_1.crhm, cartcom_1.crfield);

/*     homogenious part to right hand side of diff equation (2) */
/*     ------------------------------------------------------------------ */


    i__1 = inputcom_1.ncar * (inputcom_1.ncar - 1) + 1;
    i__2 = inputcom_1.ncar;
    for (ix = 1; i__2 < 0 ? ix >= i__1 : ix <= i__1; ix += i__2) {
	i__3 = ix - 1;
	i__4 = ix - 1;
	i__5 = ix - 1;
	z__2.r = cartcom_1.crsource[i__4].r + cartcom_1.crfield[i__5].r, 
		z__2.i = cartcom_1.crsource[i__4].i + cartcom_1.crfield[i__5]
		.i;
	i__6 = ix;
	i__7 = ix - 1;
	z__5.r = cartcom_1.crfield[i__6].r - cartcom_1.crfield[i__7].r, 
		z__5.i = cartcom_1.crfield[i__6].i - cartcom_1.crfield[i__7]
		.i;
	i__8 = ix - 1;
	z__4.r = z__5.r - cartcom_1.crfield[i__8].r, z__4.i = z__5.i - 
		cartcom_1.crfield[i__8].i;
	z__3.r = cartcom_1.cstep.r * z__4.r - cartcom_1.cstep.i * z__4.i, 
		z__3.i = cartcom_1.cstep.r * z__4.i + cartcom_1.cstep.i * 
		z__4.r;
	z__1.r = z__2.r + z__3.r, z__1.i = z__2.i + z__3.i;
	cartcom_1.crhm[i__3].r = z__1.r, cartcom_1.crhm[i__3].i = z__1.i;
	i__3 = ix + inputcom_1.ncar - 2;
	for (idx = ix + 1; idx <= i__3; ++idx) {
	    i__4 = idx - 1;
	    i__5 = idx - 1;
	    i__6 = idx - 1;
	    z__2.r = cartcom_1.crsource[i__5].r + cartcom_1.crfield[i__6].r, 
		    z__2.i = cartcom_1.crsource[i__5].i + cartcom_1.crfield[
		    i__6].i;
	    i__7 = idx;
	    i__8 = idx - 2;
	    z__6.r = cartcom_1.crfield[i__7].r + cartcom_1.crfield[i__8].r, 
		    z__6.i = cartcom_1.crfield[i__7].i + cartcom_1.crfield[
		    i__8].i;
	    i__9 = idx - 1;
	    z__5.r = z__6.r - cartcom_1.crfield[i__9].r, z__5.i = z__6.i - 
		    cartcom_1.crfield[i__9].i;
	    i__10 = idx - 1;
	    z__4.r = z__5.r - cartcom_1.crfield[i__10].r, z__4.i = z__5.i - 
		    cartcom_1.crfield[i__10].i;
	    z__3.r = cartcom_1.cstep.r * z__4.r - cartcom_1.cstep.i * z__4.i, 
		    z__3.i = cartcom_1.cstep.r * z__4.i + cartcom_1.cstep.i * 
		    z__4.r;
	    z__1.r = z__2.r + z__3.r, z__1.i = z__2.i + z__3.i;
	    cartcom_1.crhm[i__4].r = z__1.r, cartcom_1.crhm[i__4].i = z__1.i;
	}
	idx = ix + inputcom_1.ncar - 1;
	i__3 = idx - 1;
	i__4 = idx - 1;
	i__5 = idx - 1;
	z__2.r = cartcom_1.crsource[i__4].r + cartcom_1.crfield[i__5].r, 
		z__2.i = cartcom_1.crsource[i__4].i + cartcom_1.crfield[i__5]
		.i;
	i__6 = idx - 2;
	i__7 = idx - 1;
	z__5.r = cartcom_1.crfield[i__6].r - cartcom_1.crfield[i__7].r, 
		z__5.i = cartcom_1.crfield[i__6].i - cartcom_1.crfield[i__7]
		.i;
	i__8 = idx - 1;
	z__4.r = z__5.r - cartcom_1.crfield[i__8].r, z__4.i = z__5.i - 
		cartcom_1.crfield[i__8].i;
	z__3.r = cartcom_1.cstep.r * z__4.r - cartcom_1.cstep.i * z__4.i, 
		z__3.i = cartcom_1.cstep.r * z__4.i + cartcom_1.cstep.i * 
		z__4.r;
	z__1.r = z__2.r + z__3.r, z__1.i = z__2.i + z__3.i;
	cartcom_1.crhm[i__3].r = z__1.r, cartcom_1.crhm[i__3].i = z__1.i;
    }

/*     neumann boundary condition */
/*     ------------------------------------------------------------------ */

    if (inputcom_1.lbc != 0) {
	i__2 = inputcom_1.ncar;
	for (ix = 1; ix <= i__2; ++ix) {
	    idx = inputcom_1.ncar * (ix - 1) + 1;
	    i__1 = idx - 1;
	    i__3 = idx - 1;
	    i__4 = idx;
	    z__2.r = cartcom_1.cstep.r * cartcom_1.crfield[i__4].r - 
		    cartcom_1.cstep.i * cartcom_1.crfield[i__4].i, z__2.i = 
		    cartcom_1.cstep.r * cartcom_1.crfield[i__4].i + 
		    cartcom_1.cstep.i * cartcom_1.crfield[i__4].r;
	    z__1.r = cartcom_1.crhm[i__3].r + z__2.r, z__1.i = cartcom_1.crhm[
		    i__3].i + z__2.i;
	    cartcom_1.crhm[i__1].r = z__1.r, cartcom_1.crhm[i__1].i = z__1.i;
	    idx = idx + inputcom_1.ncar - 1;
	    i__1 = idx - 1;
	    i__3 = idx - 1;
	    i__4 = idx - 2;
	    z__2.r = cartcom_1.cstep.r * cartcom_1.crfield[i__4].r - 
		    cartcom_1.cstep.i * cartcom_1.crfield[i__4].i, z__2.i = 
		    cartcom_1.cstep.r * cartcom_1.crfield[i__4].i + 
		    cartcom_1.cstep.i * cartcom_1.crfield[i__4].r;
	    z__1.r = cartcom_1.crhm[i__3].r + z__2.r, z__1.i = cartcom_1.crhm[
		    i__3].i + z__2.i;
	    cartcom_1.crhm[i__1].r = z__1.r, cartcom_1.crhm[i__1].i = z__1.i;
	}
    }

/*     solve the tridiagonal system 2 */
/*     ------------------------------------------------------------------ */

    tridagy_(cartcom_1.crmatc, cartcom_1.crhm, cartcom_1.crfield);

    return 0;
} /* field_ */



/* fieldcar */
/* Subroutine */ int tridagx_(c__, r__, u)
doublecomplex *c__, *r__, *u;
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5, i__6, i__7, i__8;
    doublecomplex z__1, z__2, z__3;

    /* Local variables */
    static integer i__, k;

/*     ================================================================== */
/*     solve a tridiagonal system for cartesian mesh in x direction */
/*     cbet and cwet are precalculated in auxval */
/*     ------------------------------------------------------------------ */





/*     error codes */

/* genesis version */
/* platform */
/* indicator for original fil */
/* indicator for sdds filetyp */
/* # of particles */
/* # of integration steps */
/* # of slices */
/* maximum of harmonics */
/* maximum of particle i */
/* <> 0 keeps distribution in */
/* energy units (mc^2) in ev */
/* vacuum impedence in ohms */
/* speed of light * electron */
/* pi */
/* pi/2 */
/* 2*pi */
/* check i for precission */
/* check ii for precission */
/* number of radial points fo */
/* # of gridpoints of cartesi */


/*     function prototypes */


/*     ------------------------------------------------------ */
/*     all input variables */

/*     wiggler */
/*     electron beam */
/*     radiation */
/*     grid-quantities */
/*     control */
/*     strong focusing */
/*     loading */
/*     output */
/*     external files */
/*     time-dependency */
/*     scan */
/*     extension */


/*     -------------------------------------------------------------------- */
/*     cartesian mesh */




    /* Parameter adjustments */
    --u;
    --r__;
    --c__;

    /* Function Body */
    i__1 = inputcom_1.ncar * (inputcom_1.ncar - 1);
    i__2 = inputcom_1.ncar;
    for (i__ = 0; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	i__3 = i__ + 1;
	i__4 = i__ + 1;
	z__1.r = r__[i__4].r * cartcom_1.cbet[0].r - r__[i__4].i * 
		cartcom_1.cbet[0].i, z__1.i = r__[i__4].r * cartcom_1.cbet[0]
		.i + r__[i__4].i * cartcom_1.cbet[0].r;
	u[i__3].r = z__1.r, u[i__3].i = z__1.i;
	i__3 = inputcom_1.ncar;
	for (k = 2; k <= i__3; ++k) {
	    i__4 = k + i__;
	    i__5 = k + i__;
	    i__6 = k;
	    i__7 = k + i__ - 1;
	    z__3.r = c__[i__6].r * u[i__7].r - c__[i__6].i * u[i__7].i, 
		    z__3.i = c__[i__6].r * u[i__7].i + c__[i__6].i * u[i__7]
		    .r;
	    z__2.r = r__[i__5].r - z__3.r, z__2.i = r__[i__5].i - z__3.i;
	    i__8 = k - 1;
	    z__1.r = z__2.r * cartcom_1.cbet[i__8].r - z__2.i * 
		    cartcom_1.cbet[i__8].i, z__1.i = z__2.r * cartcom_1.cbet[
		    i__8].i + z__2.i * cartcom_1.cbet[i__8].r;
	    u[i__4].r = z__1.r, u[i__4].i = z__1.i;
	}
/* k */
	for (k = inputcom_1.ncar - 1; k >= 1; --k) {
	    i__3 = k + i__;
	    i__4 = k + i__;
	    i__5 = k;
	    i__6 = k + i__ + 1;
	    z__2.r = cartcom_1.cwet[i__5].r * u[i__6].r - cartcom_1.cwet[i__5]
		    .i * u[i__6].i, z__2.i = cartcom_1.cwet[i__5].r * u[i__6]
		    .i + cartcom_1.cwet[i__5].i * u[i__6].r;
	    z__1.r = u[i__4].r - z__2.r, z__1.i = u[i__4].i - z__2.i;
	    u[i__3].r = z__1.r, u[i__3].i = z__1.i;
	}
    }

    return 0;
} /* tridagx_ */



/* tridag */
/* Subroutine */ int tridagy_(c__, r__, u)
doublecomplex *c__, *r__, *u;
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5, i__6, i__7;
    doublecomplex z__1, z__2, z__3;

    /* Local variables */
    static integer i__, k, n;

/*     ================================================================== */
/*     solve a tridiagonal system for cartesian mesh in y direction */
/*     cbet and cwet are precalculated in auxval */
/*     ------------------------------------------------------------------ */





/*     error codes */

/* genesis version */
/* platform */
/* indicator for original fil */
/* indicator for sdds filetyp */
/* # of particles */
/* # of integration steps */
/* # of slices */
/* maximum of harmonics */
/* maximum of particle i */
/* <> 0 keeps distribution in */
/* energy units (mc^2) in ev */
/* vacuum impedence in ohms */
/* speed of light * electron */
/* pi */
/* pi/2 */
/* 2*pi */
/* check i for precission */
/* check ii for precission */
/* number of radial points fo */
/* # of gridpoints of cartesi */


/*     function prototypes */

/*     -------------------------------------------------------------------- */
/*     cartesian mesh */




/*     ------------------------------------------------------ */
/*     all input variables */

/*     wiggler */
/*     electron beam */
/*     radiation */
/*     grid-quantities */
/*     control */
/*     strong focusing */
/*     loading */
/*     output */
/*     external files */
/*     time-dependency */
/*     scan */
/*     extension */



    /* Parameter adjustments */
    --u;
    --r__;
    --c__;

    /* Function Body */
    i__1 = inputcom_1.ncar;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	i__3 = i__;
	z__1.r = r__[i__3].r * cartcom_1.cbet[0].r - r__[i__3].i * 
		cartcom_1.cbet[0].i, z__1.i = r__[i__3].r * cartcom_1.cbet[0]
		.i + r__[i__3].i * cartcom_1.cbet[0].r;
	u[i__2].r = z__1.r, u[i__2].i = z__1.i;
    }
    i__1 = inputcom_1.ncar;
    for (k = 2; k <= i__1; ++k) {
	n = k * inputcom_1.ncar - inputcom_1.ncar;
	i__2 = inputcom_1.ncar;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = n + i__;
	    i__4 = n + i__;
	    i__5 = k;
	    i__6 = n + i__ - inputcom_1.ncar;
	    z__3.r = c__[i__5].r * u[i__6].r - c__[i__5].i * u[i__6].i, 
		    z__3.i = c__[i__5].r * u[i__6].i + c__[i__5].i * u[i__6]
		    .r;
	    z__2.r = r__[i__4].r - z__3.r, z__2.i = r__[i__4].i - z__3.i;
	    i__7 = k - 1;
	    z__1.r = z__2.r * cartcom_1.cbet[i__7].r - z__2.i * 
		    cartcom_1.cbet[i__7].i, z__1.i = z__2.r * cartcom_1.cbet[
		    i__7].i + z__2.i * cartcom_1.cbet[i__7].r;
	    u[i__3].r = z__1.r, u[i__3].i = z__1.i;
	}
    }
    for (k = inputcom_1.ncar - 1; k >= 1; --k) {
	n = k * inputcom_1.ncar - inputcom_1.ncar;
	i__1 = inputcom_1.ncar;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = n + i__;
	    i__3 = n + i__;
	    i__4 = k;
	    i__5 = n + i__ + inputcom_1.ncar;
	    z__2.r = cartcom_1.cwet[i__4].r * u[i__5].r - cartcom_1.cwet[i__4]
		    .i * u[i__5].i, z__2.i = cartcom_1.cwet[i__4].r * u[i__5]
		    .i + cartcom_1.cwet[i__4].i * u[i__5].r;
	    z__1.r = u[i__3].r - z__2.r, z__1.i = u[i__3].i - z__2.i;
	    u[i__2].r = z__1.r, u[i__2].i = z__1.i;
	}
    }

    return 0;
} /* tridagy_ */




/* tridag */
/* Subroutine */ int getdiag_(stepsize, gridsize, wavenumber)
doublereal *stepsize, *gridsize, *wavenumber;
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5;
    doublecomplex z__1, z__2, z__3;

    /* Builtin functions */
    void z_div();

    /* Local variables */
    static integer icar;
    static doublereal mmid[171], mlow[171], mupp[171], rtmp;
    static doublecomplex cwrk1[171], cwrk2[171];
    static integer ix;

/*     ====================================================================== */
/*     construct the diagonal matrix for field equation */
/*     do some precalculation for field solver */
/*     ---------------------------------------------------------------------- */





/*     error codes */

/* genesis version */
/* platform */
/* indicator for original fil */
/* indicator for sdds filetyp */
/* # of particles */
/* # of integration steps */
/* # of slices */
/* maximum of harmonics */
/* maximum of particle i */
/* <> 0 keeps distribution in */
/* energy units (mc^2) in ev */
/* vacuum impedence in ohms */
/* speed of light * electron */
/* pi */
/* pi/2 */
/* 2*pi */
/* check i for precission */
/* check ii for precission */
/* number of radial points fo */
/* # of gridpoints of cartesi */


/*     function prototypes */


/*     ------------------------------------------------------ */
/*     all input variables */

/*     wiggler */
/*     electron beam */
/*     radiation */
/*     grid-quantities */
/*     control */
/*     strong focusing */
/*     loading */
/*     output */
/*     external files */
/*     time-dependency */
/*     scan */
/*     extension */


/*     -------------------------------------------------------------------- */
/*     cartesian mesh */




/*     --------------------------------------------------------------------- */
/*     working-space (no cross-use of array values in call. subroutines) */







/*     construction of the diagonal maxtrix for cartesian mesh */
/*     -------------------------------------------------------------------- */
    rtmp = *stepsize * .25 / (*wavenumber * *gridsize * *gridsize);
/* factor dz/(4 */
    z__1.r = 0., z__1.i = rtmp;
    cartcom_1.cstep.r = z__1.r, cartcom_1.cstep.i = z__1.i;
/* complex value - see field equation */
    if (inputcom_1.lbc != 0) {
	inputcom_1.lbc = 1;
    }
/* boundary condition */
    mupp[0] = rtmp;
/* one edge of mesh */
    mmid[0] = -((doublereal) (2 - inputcom_1.lbc)) * rtmp;
/* boundary condition a=0 or da/dz=0 */
    mlow[0] = 0.;
    i__1 = inputcom_1.ncar - 1;
    for (ix = 2; ix <= i__1; ++ix) {
	mupp[ix - 1] = rtmp;
/* inside of mesh -> 2nd derivation possible */
	mmid[ix - 1] = rtmp * -2.;
	mlow[ix - 1] = rtmp;
    }
    mupp[inputcom_1.ncar - 1] = 0.;
/* other edge of mesh */
    mmid[inputcom_1.ncar - 1] = -((doublereal) (2 - inputcom_1.lbc)) * rtmp;
    mlow[inputcom_1.ncar - 1] = rtmp;

/*     construct complex matrix crmat=(i-im) for */
/*     field equation  (i-im)*a(t+1)=(i+im)a(t) */
/*     ------------------------------------------------------------------------- */
    i__1 = inputcom_1.ncar;
    for (icar = 1; icar <= i__1; ++icar) {
	i__2 = icar - 1;
	i__3 = icar - 1;
	z__2.r = 0., z__2.i = mupp[i__3];
	z__1.r = -z__2.r, z__1.i = -z__2.i;
	cwrk1[i__2].r = z__1.r, cwrk1[i__2].i = z__1.i;
/* store value tem */
	i__2 = icar - 1;
	i__3 = icar - 1;
	z__2.r = 0., z__2.i = mmid[i__3];
	z__1.r = 1. - z__2.r, z__1.i = 0. - z__2.i;
	cwrk2[i__2].r = z__1.r, cwrk2[i__2].i = z__1.i;
/* same here */
	i__2 = icar - 1;
	i__3 = icar - 1;
	z__2.r = 0., z__2.i = mlow[i__3];
	z__1.r = -z__2.r, z__1.i = -z__2.i;
	cartcom_1.crmatc[i__2].r = z__1.r, cartcom_1.crmatc[i__2].i = z__1.i;
/* crmatc is used */
    }

/*     precalculated constants for tridiag subroutine */
/*     ------------------------------------------------------------------------ */
    z_div(&z__1, &c_b5, cwrk2);
    cartcom_1.cbet[0].r = z__1.r, cartcom_1.cbet[0].i = z__1.i;
    cartcom_1.cwet[0].r = (float)0., cartcom_1.cwet[0].i = (float)0.;
    i__1 = inputcom_1.ncar;
    for (icar = 2; icar <= i__1; ++icar) {
	i__2 = icar - 1;
	i__3 = icar - 2;
	i__4 = icar - 2;
	z__1.r = cwrk1[i__3].r * cartcom_1.cbet[i__4].r - cwrk1[i__3].i * 
		cartcom_1.cbet[i__4].i, z__1.i = cwrk1[i__3].r * 
		cartcom_1.cbet[i__4].i + cwrk1[i__3].i * cartcom_1.cbet[i__4]
		.r;
	cartcom_1.cwet[i__2].r = z__1.r, cartcom_1.cwet[i__2].i = z__1.i;
	i__2 = icar - 1;
	i__3 = icar - 1;
	i__4 = icar - 1;
	i__5 = icar - 1;
	z__3.r = cartcom_1.crmatc[i__4].r * cartcom_1.cwet[i__5].r - 
		cartcom_1.crmatc[i__4].i * cartcom_1.cwet[i__5].i, z__3.i = 
		cartcom_1.crmatc[i__4].r * cartcom_1.cwet[i__5].i + 
		cartcom_1.crmatc[i__4].i * cartcom_1.cwet[i__5].r;
	z__2.r = cwrk2[i__3].r - z__3.r, z__2.i = cwrk2[i__3].i - z__3.i;
	z_div(&z__1, &c_b5, &z__2);
	cartcom_1.cbet[i__2].r = z__1.r, cartcom_1.cbet[i__2].i = z__1.i;
    }
    return 0;
} /* getdiag_ */

