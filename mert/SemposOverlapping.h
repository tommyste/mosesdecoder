#ifndef MERT_SEMPOSOVERLAPPING_H_
#define MERT_SEMPOSOVERLAPPING_H_

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

// TODO: need to comments about this number.
const int kMaxNOC = 30;

typedef std::pair<std::string, std::string> str_item_t;
typedef std::vector<str_item_t> str_sentence_t;
typedef str_sentence_t::const_iterator str_sentence_it;

typedef std::pair<int,int> item_t;
typedef std::multiset<item_t> sentence_t;
typedef sentence_t::const_iterator sentence_it;

/**
 * An interface for classes representing overlapping formulas
 */
class SemposOverlapping
{
public:
  virtual ~SemposOverlapping() {}
  virtual std::vector<int> prepareStats(const sentence_t& cand, const sentence_t& ref) = 0;
  virtual float calculateScore(const std::vector<int>& stats) const = 0;
  virtual std::size_t NumberOfScores() const = 0;
};

class SemposOverlappingFactory {
 public:
  static SemposOverlapping* GetOverlapping(const std::string& str);

  // dependency injection for unit testing.
  static void SetOverlapping(SemposOverlapping* ovr);

 private:
  SemposOverlappingFactory() {}
  ~SemposOverlappingFactory() {}
};

/**
 * Overlapping proposed by (Bojar and Machacek, WMT 2011)
 *
 * Please refer to the paper for details:
 * http://aclweb.org/anthology-new/W/W11/W11-2108.pdf
 */
class CapMicroOverlapping : public SemposOverlapping
{
public:
  CapMicroOverlapping() {}
  ~CapMicroOverlapping() {}

  virtual std::vector<int> prepareStats(const sentence_t& cand, const sentence_t& ref);
  virtual float calculateScore(const std::vector<int>& stats) const;
  virtual std::size_t NumberOfScores() const { return 2; }

 private:
  // no copying allowed.
  CapMicroOverlapping(const CapMicroOverlapping&);
  CapMicroOverlapping& operator=(const CapMicroOverlapping&);
};

/**
 * Overlapping proposed by (Kos and Bojar, 2009)
 */
class CapMacroOverlapping : public SemposOverlapping
{
public:
  CapMacroOverlapping() {}
  ~CapMacroOverlapping() {}

  virtual std::vector<int> prepareStats(const sentence_t& cand, const sentence_t& ref);
  virtual float calculateScore(const std::vector<int>& stats) const;
  virtual std::size_t NumberOfScores() const { return kMaxNOC * 2; }

 private:
  // no copying allowed.
  CapMacroOverlapping(const CapMacroOverlapping&);
  CapMacroOverlapping& operator=(const CapMacroOverlapping&);
};

#endif  // MERT_SEMPOSOVERLAPPING_H_
