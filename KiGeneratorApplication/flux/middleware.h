#ifndef MIDDLEWARE1_H
#define MIDDLEWARE1_H
#include <QSharedPointer>

namespace vtx
{
namespace flux
{
class Action;

class Middleware
{
public:
    virtual ~Middleware() = default;

    virtual QSharedPointer<Action> process(const QSharedPointer<Action>& action) = 0;

protected:
    Middleware() = default;
    Middleware(const Middleware&) = default;
    Middleware(Middleware&&) = default;
    Middleware& operator=(const Middleware&) = default;
    Middleware& operator=(Middleware&&) = default;
};
}
}
#endif // MIDDLEWARE_H
