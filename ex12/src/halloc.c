#include <unistd.h>
#include <errno.h>

static inline size_t     word_align (size_t size)
{
  return ((((((size) - 1) >> 3) << 3) + 8));
};

typedef struct s_chunk
{
  size_t             size;
  void               *data;
  int                free;
  struct s_chunk     *prev, *next;
} *t_chunk;

static void *halloc_base ()
{
  static t_chunk      b;

  b = NULL;
  if (!b)
  {
    b = sbrk(word_align(sizeof(struct s_chunk)));
    if (b == (void*) -1)
    {
      return (NULL);
    }
    b->next = NULL;
    b->prev = NULL;
    b->size = 0;
    b->free = 0;
    b->data = NULL;
  }

  return (b);
};

t_chunk     find_chunk (t_chunk *last, size_t size)
{
  t_chunk     b;

  b = halloc_base();
  while (b && !(b->free && b->size >= size))
  {
    *last = b;
    b = b->next;
  }
  return (b);
};

void     split_chunk (t_chunk b, size_t size)
{
  t_chunk     new_ch;

  new_ch       = (t_chunk)(b->data + size);
  new_ch->prev = b;
  new_ch->next = b->next;
  new_ch->size = b->size - size;
  new_ch->free = 1;
  new_ch->data = new_ch + 1;
  b->size = size - sizeof(struct s_chunk);
  b->next = new_ch;
  if (b->next)
    b->next->prev = new_ch;
};

void     *halloc (size_t size)
{
  size_t     len;
  t_chunk    prev, b;

  if (!size)
    return (NULL);
  prev = NULL;
  len  = word_align(size + sizeof(struct s_chunk));
  b  = find_chunk(&prev, size);
  if (!b)
  {
    t_chunk     new_ch;

    new_ch = sbrk(len);
    if (new_ch == (void*) -1)
      return (NULL);
    new_ch->next = NULL;
    new_ch->prev = prev;
    new_ch->size = len - sizeof(struct s_chunk);
    new_ch->data = new_ch + 1;
    prev->next = new_ch;
    b = new_ch;
  }
  else if (len + sizeof(size_t) < b->size)
    split_chunk(b, len);
  b->free = 0;

  return (b->data);
};

void     merge_next (t_chunk b)
{
  b->size = b->size + b->next->size + sizeof(struct s_chunk);
  b->next = b->next->next;
  if (b->next)
    b->next->prev = b;
};

void     my_free (void *ptr)
{
  if (!ptr || ptr < halloc_base() || ptr > sbrk(0))
    return;
  t_chunk     b;

  b = (t_chunk) ptr - 1;
  if (b->data != ptr)
    return;
  b->free = 1;
  if (b->next && b->next->free)
    merge_next(b);
  if (b->prev->free)
    merge_next(b = b->prev);
  if (!b->next)
  {
    b->prev->next = NULL;
    sbrk(b->size - sizeof(struct s_chunk));
  }
};

