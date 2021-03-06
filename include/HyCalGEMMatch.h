#ifndef HYCALGEMMATCH_H
#define HYCALGEMMATCH_H
#include <vector>
#include <cstring>
#include "datastruct.h"
#include "GEMDataStruct.h"
#include "PRadEventStruct.h"

class GEMCoord;

class HyCalGEMMatch
{
public:
    HyCalGEMMatch();
    ~HyCalGEMMatch();
    void SetGEMCoord(GEMCoord * fgemcoord);
    void SetHyCalVector(std::vector<HyCalHit> * hycalhit);
    std::vector<GEMClusterStruct> & GetMatchGEM();
    std::vector<GEMClusterStruct> & GetMatchGEM1();
    std::vector<GEMClusterStruct> & GetMatchGEM2();
    std::vector<HyCalHit> & GetMatchHyCal();
    std::vector<HyCalHit> & GetMatchHyCalGEM1();
    std::vector<HyCalHit> & GetMatchHyCalGEM2();
    void Clear();
    void Reset();

    // Note 1:
    // match starting from hycal, for each cluster on hycal
    // look up matching cluster on gem. 
    // gem matching results will be organized into one plane.
    int Match();
    int MetaMatch();
    // Note 2: 
    // match starting from hycal, for each cluster on hycal
    // look up matching cluster on gem.
    // for single-gem moller events to detect offset
    // each gem chamber has its own matching result.
    void MatchByGEM(); 
    void MetaMatchByGEM(std::vector<GEMClusterStruct> & _gem, 
	    std::vector<GEMClusterStruct> & _res,
	    std::vector<HyCalHit> &_hycal);
    // Note 3:
    // match starting from gem, for each cluster on gem
    // look up matching cluster on hycal.
    // for calibration run, distinguish e+ from e-
    // each gem gem chamber has its own matching result.
    //void MatchAccordToGEM();
    //void MetaMatchAccordToGEM(std::vector<GEMClusterStruct> & _gem, 
//	    std::vector<GEMClusterStruct> & _res);
    
    // match core algorithm
    int SinglePointMatchAlgorithm(double &match_criteria, std::vector<GEMClusterStruct> &, 
        std::vector<HyCalHit> *, int & hycal_index, int & match_index);
    void ShowMatch(); // show match process

    void SetMatchCriteria(double & );
    void SetMatchCriteria(double &&);
    void SetGEM1Z(double &);
    void SetGEM2Z(double &);
    void SetHyCalZ(double &);
    double r(double &, double &);
    double r(double &&, double &&);
    void ProjectHyCalToPlaneZ(double &, double &, double &);

private:
    GEMCoord *gem_coord;
    std::vector<GEMClusterStruct> res_gem;
    std::vector<GEMClusterStruct> res_gem1;
    std::vector<GEMClusterStruct> res_gem2;
    std::vector<HyCalHit> res_hycal;
    std::vector<HyCalHit> res_hycal_gem1;
    std::vector<HyCalHit> res_hycal_gem2; 
    std::vector<GEMClusterStruct> gem[2];
    std::vector<HyCalHit> *hycal_hit;

    double z_gem1;
    double z_gem2;
    double z_hycal;
    double delta;

    // show match
    int n_match;
};

#endif
