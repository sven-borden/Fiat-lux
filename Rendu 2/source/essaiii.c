#include <stdlib.h>
#include <stdio.h>

modeleParallelisme ( VECTOR x, VECTOR y)
{
nx = utilitaireNormeVector (x) ;
ny = utilitaireNormeVector (y) ;
VECTOR ux = { x.ptDeb/nx ,x.ptFin/nx)};
VECTOR uy = { y.ptDeb/ny ,y.ptFin/ny};
VECTOR nx = { -ux.ptFin , ux.ptDeb}; 
VECTOR ny = { -uy.ptFin , uy.ptDeb}; 
VECTOR vd1d2 = { y.ptDeb-a.ptDeb , y.ptDeb- x.ptDeb};
nvd1d2 = utilitaireNormeVector(vd1d2);
VECTOR ud1d2 = { vd1d2.ptDeb/nvd1d2 , vd1d2.ptFin/nvd1d2};

// détection du parallélisme et/ou de la superposition
pv_u1_u2 = utilitaireProduitVectoriel (ux,uy);

if (fabs(pv_u1_u2)<= EPSIL_PARAL
	pvdeb = utilitaireProduitVectoriel(ux, ud1d2) ;
	if ( fabs (pvdeb) <= EPSIL_PARAL)
	//determiner si superposition a completer
	ps_ux_y = utilitaireProduitScalaire(ux, y);
	psdeb = utilitaireProduitScalaire(ux, vd1d2);
	else return 0;
else return 1;

}

// detection d'une éventuelle intersection pour des segments non parallèles
int modeleIntersection ( VECTOR x, VECTOR y)
{
nx = utilitaireNormeVector (x) ;
ny = utilitaireNormeVector (y) ;
VECTOR ux = { x.ptDeb/nx ,x.ptFin/nx)} ;
VECTOR uy = { y.ptDeb/ny ,y.ptFin/ny};
VECTOR nx = { -ux.ptFin , ux.ptDeb}; 
VECTOR ny = { -uy.ptFin , uy.ptDeb}; 
VECTOR vd1d2 = { y.ptDeb-a.ptDeb , y.ptDeb- x.ptDeb};
nvd1d2 = utilitaireNormeVector(vd1d2);
VECTOR ud1d2 = { vd1d2.ptDeb/nvd1d2 , vd1d2.ptFin/nvd1d2};

projette_vd1d2_n1 = utilitaireProduitScalaire( VECTOR n1, VECTOR vd1d2);
projette_vd2f1_n2 = utilitaireProduitScalaire( VECTOR n2, VECTOR vd2f1);
projette_vd1f2_n1 = utilitaireProduitScalaire( VECTOR n1, VECTOR vd1d2);
projette_vd1d2_n2 = utilitaireProduitScalaire( VECTOR n1, VECTOR vd1d2);

if (fabs(projette_vd1d2_n1 < EPSIL_CONTACT))|| (fabs(projette_vd1f2_n1) < EPSIL_CONTACT) || (projette_vd1d2_n1*projette_vd1f2_n1<0 )
	if (fabs(projette_vd1d2_n1 < EPSIL_CONTACT))|| (fabs(projette_vd1f2_n1) < EPSIL_CONTACT) || (projette_vd1d2_n2*projette_vd1f2_n2<0 )
		return 1;
}

POINT modelePointIntersection (VECTOR x,VECTOR y )
{
nx = utilitaireNormeVector (x) ;
ny = utilitaireNormeVector (y) ;
VECTOR ux = { x.ptDeb/nx ,x.ptFin/nx) ;
VECTOR uy = { y.ptDeb/ny ,y.ptFin/ny};
VECTOR nx = { -ux.ptFin , ux.ptDeb}; 
VECTOR ny = { -uy.ptFin , uy.ptDeb}; 
VECTOR vd1d2 = { y.ptDeb-a.ptDeb , y.ptDeb- x.ptDeb};
nvd1d2 = utilitaireNormeVector(vd1d2);
VECTOR ud1d2 = { vd1d2.ptDeb/nvd1d2 , vd1d2.ptFin/nvd1d2};

projette_vd1d2_n1 = utilitaireProduitScalaire( VECTOR n1, VECTOR vd1d2);
projette_vd2f1_n2 = utilitaireProduitScalaire( VECTOR n2, VECTOR vd2f1);
projette_vd1f2_n1 = utilitaireProduitScalaire( VECTOR n1, VECTOR vd1d2);
projette_vd1d2_n2 = utilitaireProduitScalaire( VECTOR n1, VECTOR vd1d2);

if (fabs(projette_vd1d2_n1 < EPSIL_CONTACT))|| (fabs(projette_vd1f2_n1) < EPSIL_CONTACT) || (projette_vd1d2_n1*projette_vd1f2_n1<0 )
	if (fabs(projette_vd1d2_n1 < EPSIL_CONTACT))|| (fabs(projette_vd1f2_n1) < EPSIL_CONTACT) || (projette_vd1d2_n2*projette_vd1f2_n2<0 )
	
POINT  P = { x.ptDeb.x + [( utilitaireProduitVectoriel(uy, vd1d2)/ utilitaireProduitVectoriel (uy, ux)]*ux.ptDeb,
	          x.ptDeb.y + [( utilitaireProduitVectoriel(uy, vd1d2)/ utilitaireProduitVectoriel (uy, ux)]*ux.ptFin} ;
}


}

double utilitaireProduitScalaire ( VECTOR a, VECTOR b) 
{
	double ps = ( a.ptDeb*b.ptDeb + a.ptFin*b.ptFin);
	return ps;
	
}	

double utilitaireProduitVectoriel (VECTOR a,VECTOR b)
{
	double pv ;
	pv = (a.ptDeb*b.ptFin - a.ptFin*b.ptDeb);
return pv ;
}

//on mets les memes noms?
// nom trop long? 



