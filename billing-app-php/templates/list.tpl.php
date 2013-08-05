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
    <?php if (!empty($this->links)) : ?>
    <div>
      <ul>
      <?php foreach ($this->links as $link) : ?>
        <li>
          <a href="<?php echo $link['href'];?>"><?php echo $link['title']; ?></a>
        </li>
      <?php endforeach; ?>
      </ul>
    </div>
    <?php endif; ?>
    <table>
    <?php if (!empty($this->header)) : ?>
      <thead>
        <tr>
          <?php foreach ($this->header as $head) : ?>
          <th><?php echo $head; ?></th>
          <?php endforeach; ?>
        </tr>
      </thead>
      <?php endif; ?>
      <tbody>
        <?php foreach ($this->rows as $row) : ?>
        <tr>
          <?php foreach ($row as $value) : ?>
          <td><?php echo $value; ?></td>
          <?php endforeach; ?>
        </tr>
        <?php endforeach; ?>
      </tbody>
    </table>
  </body>
</html>

