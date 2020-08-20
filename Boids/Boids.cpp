#include <iostream>
#include "Particle.h"
#include "CImg.h"
#include <list>
#include "Vector2.h"
#include <string>

void LoopWindow(Particle*);
bool InRange(Particle*, Particle*);
Vector2 Alignment(Particle*, std::list<Particle*>);
Vector2 Cohesion(Particle*, std::list<Particle*>);
Vector2 Separation(Particle*, std::list<Particle*>);

#define WIDTH  1080
#define HEIGHT 720 
#define FLOCK_SIZE 75

using namespace cimg_library;

int main()
{
    auto _fps_timer = cimg::time();
    float delta;
    std::list<Particle*> flock;
    unsigned char flockColor[3] = { 255,255,255 };
    unsigned char separationColor[3] = { 64,255,64 };
    
    for (int i = 0; i < FLOCK_SIZE; i++) {
        Vector2* location = new Vector2((rand() % WIDTH), (rand() % HEIGHT));
        unsigned int radius = 3;
        Particle* newFlockMember = new Particle(radius, *location);
        newFlockMember->velocity = Vector2(0,0);
        newFlockMember->awarenessRadius = newFlockMember->radius + newFlockMember->radius * newFlockMember->radius + 50;
        newFlockMember->maxForce = 160;
        flock.push_back(newFlockMember);
    }

    CImgDisplay main_display(WIDTH, HEIGHT, "Title");
    while (!main_display.is_closed()) {
        CImg<unsigned char> img(WIDTH, HEIGHT, 1, 3, 0);
        delta = (cimg::time() - _fps_timer) / 1000.0f;
        Vector2 mousePos = Vector2(main_display.mouse_x(), main_display.mouse_y());

        for (Particle* self : flock) {
            std::list<Particle*> colidedParticles;
            for (Particle* other : flock) {
                if (self == other) continue;
                if (InRange(self, other)) {
                    colidedParticles.push_back(other);
                }
            }

            if (rand() % 10000 < 2) {
                self->intersted = !self->intersted;
                if (self->intersted) {
                    self->PoI = Vector2(rand() % WIDTH, rand() % HEIGHT);
                }
            }
            
            Vector2 alignmentForce = Alignment(self, colidedParticles);
            Vector2 cohesionForce = Cohesion(self, colidedParticles);
            Vector2 separationForce = Separation(self, colidedParticles);
            
            self->acceleration += separationForce;
            self->acceleration += cohesionForce;
            self->acceleration += alignmentForce;

            if (self->intersted) {
                Vector2 dir = (self->PoI - self->position).Normalized();
                self->acceleration += dir * self->interestDesire / (self->aligmentDesire + self->aligmentDesire + self->cohesionDesire + self->interestDesire) * 20;
            }
            
            float dstFromMouse = (self->position - mousePos).LenghtSquared();
            if (main_display.button() == 1 && dstFromMouse <= 200*200) {
                self->acceleration += (mousePos - self->position).Normalized() * 25;
            }
            if (main_display.button() == 2 && dstFromMouse <= 200 * 200) {
                self->acceleration += (self->position - mousePos).Normalized() * 25;
            }
            self->velocity += self->acceleration;

            /*
            if (self->velocity.LenghtSquared() > self->maxForce * self->maxForce) {
                float ratio = self->maxForce / self->velocity.Lenght();
                self->velocity *= ratio;
            }
            */
            self->position += self->velocity.Normalized() * delta * 1000;
            self->acceleration = Vector2(0, 0);

            LoopWindow(self);

            img.draw_circle(self->position.x, self->position.y, self->radius, flockColor, 1);
            if (self->intersted) {
                if ((self->position - self->PoI).LenghtSquared() < 200) {
                    self->intersted = false;
                }
                img.draw_circle(self->PoI.x, self->PoI.y, 2, separationColor, 1);
            }
            
            
            if (main_display.is_keySPACE()) {
                Vector2 direction = self->velocity.Normalized() * 20;
                img.draw_arrow(self->position.x, self->position.y, self->position.x + separationForce.x, self->position.y + separationForce.y, separationColor, 1);
                img.draw_circle(self->position.x, self->position.y, self->awarenessRadius, flockColor, 0.01f);
                img.draw_arrow(self->position.x, self->position.y, self->position.x + direction.x, self->position.y + direction.y, flockColor, 1);
            }

            if (main_display.is_keyA())
                self->aligmentDesire += delta * 2;
            if (main_display.is_keyS()) 
                self->aligmentDesire -= delta * 2;
            if (main_display.is_keyZ()) 
                self->cohesionDesire += delta * 2;
            if (main_display.is_keyX()) 
                self->cohesionDesire -= delta * 2;
            if (main_display.is_keyD()) 
                self->separationDesire += delta * 2;
            if (main_display.is_keyF()) 
                self->separationDesire -= delta * 2;
            if (main_display.is_keyC()) 
                self->interestDesire += delta * 2;
            if (main_display.is_keyV()) 
                self->interestDesire -= delta * 2;

            colidedParticles.clear();
        }

        img.draw_circle(mousePos.x, mousePos.y, 200, flockColor, 0.005f);

        unsigned char color[3] = { 255, 255, 255 };
        auto str = std::to_string(main_display.frames_per_second()) + "\n";
        str += std::to_string(delta) + "\n";
        str = std::to_string(main_display.frames_per_second()) + "\n";
        str += "aligment: " + std::to_string(flock.front()->aligmentDesire) + "\n";
        str += "cohesion: " + std::to_string(flock.front()->cohesionDesire) + "\n";
        str += "separation: " + std::to_string(flock.front()->separationDesire) + "\n";
        str += "interest: " + std::to_string(flock.front()->interestDesire) + "\n";
        img.draw_text(0, 0, str.c_str(), color, 0, 1, 20);
        _fps_timer = cimg::time();
        main_display.display(img);

        //main_display.wait();
    }
}

void LoopWindow(Particle* p) {
    if (p->position.x > WIDTH) p->position.x = 0;
    if (p->position.x < 0) p->position.x = WIDTH;
    if (p->position.y > HEIGHT) p->position.y = 0;
    if (p->position.y < 0) p->position.y = HEIGHT;
}

bool InRange(Particle* a, Particle* b) {
    Vector2 direction = b->position - a->position;
    int colisionRadius = a->awarenessRadius + b->radius;
    return(direction.LenghtSquared() <= colisionRadius * colisionRadius);
}

Vector2 Alignment(Particle* self, std::list<Particle*> others) {
    if (others.size() == 0) return Vector2(0,0);
    Vector2 avg;
    for (Particle* p : others)
        avg += p->velocity;

    avg /= (int)others.size();
    return (avg - self->velocity) * self->aligmentDesire / (self->aligmentDesire + self->aligmentDesire + self->cohesionDesire + self->interestDesire);
}

Vector2 Cohesion(Particle* self, std::list<Particle*> others) {
    if (others.size() == 0) return Vector2(0, 0);
    Vector2 avg;
    for (Particle* p : others)
        avg += p->position;

    avg /= (int)others.size();
    return (avg - self->position) * self->cohesionDesire / (self->aligmentDesire + self->aligmentDesire + self->cohesionDesire + self->interestDesire);
}

Vector2 Separation(Particle* self, std::list<Particle*> others) {
    if (others.size() == 0) return Vector2(0, 0);
    Vector2 avg;
    for (Particle* p : others) {
        Vector2 pathToOther = (self->position - p->position);
        Vector2 direction = pathToOther.Normalized();
        Vector2 Desired = direction * (float)self->radius * 2;
        avg += Desired;
    }
    return avg * self->separationDesire / (self->aligmentDesire + self->aligmentDesire + self->cohesionDesire + self->interestDesire);
}