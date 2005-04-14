# echo "Setting NtupleCompare v0 in /nfs/farm/g/glast/u06/chen/svac"

if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/slac.stanford.edu/g/glast/applications/CMT/v1r16p20040701; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh

tempfile=`${CMTROOT}/mgr/cmt build temporary_name -quiet`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt -quiet setup -sh -pack=NtupleCompare -version=v0 -path=/nfs/farm/g/glast/u06/chen/svac  $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

