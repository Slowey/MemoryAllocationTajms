#pragma once
class Graphics
{
public:
   static Graphics* Get();

private:
   Graphics();
   ~Graphics();

   static Graphics* m_singleton;
};

