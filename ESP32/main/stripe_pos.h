#ifndef M_STRIPE_POS_H
#define M_STRIPE_POS_H

class CStripePosition {
  private:
    const &CStripePosition operator=(const &CStripePosition);

    unsigned int pos;
    bool to_down;

  public:
    CStripePosition(): pos(0), to_down(true) {
    }

    void up();
    void down();
    void left();
    void right();

};

#endif