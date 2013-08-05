<html>
  <head>
    <title>Billing application</title>
  </head>
  <body>
    <?php if (!empty($this->title)) : ?>
    <div>
      <h1><?php echo $this->title; ?></h1>
    </div>
    <?php endif; ?>
    <?php if (!empty($this->main_links)) : ?>
    <div>
      <ul>
      <?php foreach ($this->main_links as $link) : ?>
        <li>
          <a href="<?php echo $link['href'];?>"><?php echo $link['title']; ?></a>
        </li>
      <?php endforeach; ?>
      </ul>
    </div>
    <div>
    <?php endif; ?>
    <?php if (!empty($this->links)) : ?>
      <ul>
      <?php foreach ($this->links as $link) : ?>
        <li>
          <a href="<?php echo $link['href'];?>"><?php echo $link['title']; ?></a>
        </li>
      <?php endforeach; ?>
      </ul>
    </div>
    <?php endif; ?>
    <?php if (!empty($this->inputs)) : ?>
      <div>
        <?php echo $this->inputs; ?>
      </div>
    <?php endif; ?>
  </body>
</html>
