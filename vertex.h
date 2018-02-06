#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <QString>

class Vertex : public glm::vec3 {
public:
    Vertex();
    Vertex(glm::vec3 v);
    Vertex(float x, float y, float z);


    void set(float x, float y, float z);
    void translate(float x, float y, float z);

    QString toString();

    bool operator==(const Vertex &v) const;

    typedef float value_type;

private:
};

// http://en.cppreference.com/w/cpp/utility/hash
// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key/17017281#17017281
namespace std {
    template<> struct hash<Vertex> {
        typedef Vertex argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const &v) const {
            return ((hash<int>()(floorf(v.x*1000.0)) ^
                     (hash<int>()(floorf(v.y*1000.0)) << 1)) >> 1) ^
                    (hash<int>()(floorf(v.z*1000.0)) << 1);
        }
    };
}

#endif // VERTEX_H
