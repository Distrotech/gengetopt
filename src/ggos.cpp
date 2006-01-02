//
// C++ Implementation: ggos
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "ggos.h"

using namespace std;

ostream & operator <<(std::ostream &s, gengetopt_option &opt)
{
  s << "long: " << opt.long_opt << ", short: " << opt.short_opt << "\n"
    << "desc: " << opt.desc;

  s << endl;

  return s;
}
