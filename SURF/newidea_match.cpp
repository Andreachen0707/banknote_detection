Mat img = imread(filename);
cv::Feature2D *detector = new cv::OrbFeatureDetector();
cv::Feature2D *extractor = new cv::OrbDescriptorExtractor();
detector->detect(img, kpImg);
extractor->compute(img, kpImg, descImg);

BruteForceMatcher< L2 > matcher;
matcher.knnMatch(desc1, desc2, matches1, 2);
matcher.knnMatch(desc2, desc1, matches2, 2);
 
ratioTest(matches1);
ratioTest(matches2);
 
symmetryTest(matches1, matches2, symMatches);


int ratioTest( VVecMatch &matches )
{
  float ratio = 0.8f;
  int removed=0;
  // for all matches
  for (std::vector<std::vector>::iterator
	matchIterator= matches.begin();
	matchIterator!= matches.end(); ++matchIterator)
  {
	// if 2 NN has been identified
	if (matchIterator->size() > 1)
	{
	  // check distance ratio
	  if ((*matchIterator)[0].distance/(*matchIterator)[1].distance > ratio) 
		{
		  matchIterator->clear(); // remove match
		  removed++;
	  }
	} else { // does not have 2 neighbours
	  matchIterator->clear(); // remove match
	  removed++;
	}
  }
  return removed;
}

void symmetryTest( const VVecMatch matches1, const VVecMatch matches2, VecMatch& symMatches )
{
  // for all matches image 1 -> image 2
  for (std::vector<std::vector>::const_iterator matchIterator1= matches1.begin();
	matchIterator1!= matches1.end(); ++matchIterator1)
  {
	// ignore deleted matches
	if (matchIterator1->size() < 2)
	  continue;
 
	// for all matches image 2 -> image 1
	for (std::vector<std::vector>::const_iterator matchIterator2= matches2.begin();
	  matchIterator2!= matches2.end();
	  ++matchIterator2)
	{
	  // ignore deleted matches
	  if (matchIterator2->size() < 2)
		continue;
	  // Match symmetry test
	  if ((*matchIterator1)[0].queryIdx ==
		 (*matchIterator2)[0].trainIdx &&
		 (*matchIterator2)[0].queryIdx ==
		 (*matchIterator1)[0].trainIdx)
		{
		 // add symmetrical match
		 symMatches.push_back(
		   cv::DMatch((*matchIterator1)[0].queryIdx,
		   (*matchIterator1)[0].trainIdx,
		   (*matchIterator1)[0].distance));
		 break; // next match in image 1 -> image 2
	  }
	}
  }
}

