#ifndef ACTION1_H
#define ACTION1_H
#include <type_traits>
#include <utility>
#include <QVariant>
#include <QSharedPointer>
#include <QVector>
#include <memory>
#include "model/innermessage.h"
namespace vtx
{
    namespace flux
    {
        template<typename E>
        using is_scoped_enum = std::integral_constant < bool, std::is_enum<E>::value && !std::is_convertible<E, int>::value >;

        class Action final
        {
            public:
                template <class ScopedEnum, class = typename std::enable_if<is_scoped_enum<ScopedEnum>::value>::type>
                Action(ScopedEnum type, QVariant& payload, bool error = false)
                    : type_(static_cast<int>(type)), payload_(payload), error_(error)
                {
                }

                template <class ScopedEnum, class = typename std::enable_if<is_scoped_enum<ScopedEnum>::value>::type>
                Action(ScopedEnum type, QVariant && payload = QVariant(), bool error = false)
                    : type_(static_cast<int>(type)), payload_(std::move(payload)), error_(error)
                {
                }

                Action(const Action&) = default;
                Action(Action&&) = default;
                Action& operator=(const Action&) = default;
                Action& operator=(Action&&) = default;
                ~Action() = default;

                template <class ScopedEnum, class = typename std::enable_if<is_scoped_enum<ScopedEnum>::value>::type>
                ScopedEnum getType() const
                {
                    return static_cast<ScopedEnum>(type_);
                }

                template<class T>
                T getPayload() const
                {
                    return qvariant_cast<T>(payload_);
                }

                bool getError() const
                {
                    return error_;
                }


                void setInnerMessage(const QSharedPointer<InnerMessage>& innerMessage)
                {
                    mInnerMessage = innerMessage;
                }

                QSharedPointer<InnerMessage> getInnerMessage() const
                {
                    return mInnerMessage;
                }


            private:
                int type_;
                QVariant payload_;
                bool error_;
                QSharedPointer<InnerMessage> mInnerMessage;
        };



    }
}
#endif // ACTION_H
