#ifndef MESSAGE_H
#define MESSAGE_H

class QDataStream;

/*!
 * \brief The Message struct is an Interface for all messages
 *        used within the application
 */
struct IMessage
{
    unsigned id;

    /*!
     * \brief Serialize the message in a sequence of Bytes
     *
     * \param stram is the container where raw bytes are written
     */
    virtual void serialize(QDataStream& stream) const = 0;

    /*!
     * \brief Deserialize message from raw bytes into the data structure
     * \param stream is the container where raw bytes are stored
     */
    virtual void deserialize(QDataStream& stream) = 0;
};

#endif // MESSAGE_H
