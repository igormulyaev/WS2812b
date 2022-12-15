#ifndef DIRECTOR_H
#define DIRECTOR_H

class Director
{
  public:
    Director ();
    ~Director ();

  private:
    Director (const Director &) = delete;
    Director & operator=(const Director &) = delete;
};

#endif